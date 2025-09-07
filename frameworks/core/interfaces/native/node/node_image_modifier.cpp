/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_image_modifier.h"

#include "effect/color_filter.h"

#include "core/common/card_scope.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/image/image_component.h"
#include "core/components/image/image_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 1;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_12 = 12;
constexpr int DEFAULT_LENGTH = 4;
constexpr int RESIZEABLE_VEC_LENGTH = 12;
constexpr CopyOptions DEFAULT_IMAGE_COPYOPTION = CopyOptions::None;
constexpr bool DEFAULT_SYNC_LOAD_VALUE = false;
constexpr ImageFit DEFAULT_OBJECT_FIT_VALUE = ImageFit::COVER;
constexpr bool DEFAULT_FIT_ORIGINAL_SIZE = false;
constexpr bool DEFAULT_DRAGGABLE = false;
constexpr bool DEFAULT_IMAGE_SENSITIVE = false;
constexpr ArkUI_Float32 DEFAULT_IMAGE_EDGE_ANTIALIASING = 0;
const std::vector<float> DEFAULT_COLOR_FILTER = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };
constexpr int32_t LOAD_ERROR_CODE = 401;
constexpr int32_t IMAGE_LOAD_STATUS_INDEX = 0;
constexpr int32_t IMAGE_WIDTH_INDEX = 1;
constexpr int32_t IMAGE_HEIGHT_INDEX = 2;
constexpr int32_t IMAGE_COMPONENT_WIDTH_INDEX = 3;
constexpr int32_t IMAGE_COMPONENT_HEIGHT_INDEX = 4;
constexpr int32_t IMAGE_CONTENT_OFFSET_X_INDEX = 5;
constexpr int32_t IMAGE_CONTENT_OFFSET_Y_INDEX = 6;
constexpr int32_t IMAGE_CONTENT_WIDTH_INDEX = 7;
constexpr int32_t IMAGE_CONTENT_HEIGHT_INDEX = 8;
constexpr uint32_t MAX_COLOR_FILTER_SIZE = 20;
constexpr uint32_t ERROR_UINT_CODE = -1;
constexpr int32_t DEFAULT_FALSE = 0;
constexpr uint32_t FIT_MATRIX = 16;
constexpr float HDR_BRIGHTNESS_MIN = 0.0f;
constexpr float HDR_BRIGHTNESS_MAX = 1.0f;
constexpr float DEFAULT_HDR_BRIGHTNESS = 1.0f;
const std::vector<ResizableOption> directions = { ResizableOption::TOP, ResizableOption::RIGHT,
    ResizableOption::BOTTOM, ResizableOption::LEFT };
thread_local std::string g_strValue;

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};

void SetOptionalBorder(std::optional<Dimension>& optionalDimension, const ArkUI_Float32* values, ArkUI_Int32 valuesSize,
    ArkUI_Int32& offset)
{
    bool hasValue = static_cast<bool>(values[offset]);
    if (hasValue) {
        optionalDimension =
            Dimension(values[offset + NUM_1], static_cast<OHOS::Ace::DimensionUnit>(values[offset + NUM_2]));
    }
    offset = offset + NUM_3;
}

bool SetCalcDimension(std::optional<CalcDimension>& optDimension, const ArkUIStringAndFloat* options,
    ArkUI_Int32 optionsLength, ArkUI_Int32 offset)
{
    if ((options == nullptr) || (offset < 0) || ((offset + NUM_3) > optionsLength)) {
        return false;
    }
    auto hasValue = options[offset];
    auto value = options[offset + NUM_1];
    auto unit = options[offset + NUM_2];
    if (static_cast<bool>(hasValue.value)) {
        auto unitValue = static_cast<DimensionUnit>(unit.value);
        if (unitValue == DimensionUnit::CALC) {
            std::string str;
            if (value.valueStr != nullptr) {
                str = value.valueStr;
            }
            CalcDimension calcDimension(str, unitValue);
            optDimension = calcDimension;
        } else {
            CalcDimension calcDimension(value.value, unitValue);
            optDimension = calcDimension;
        }
    }
    return true;
}

void SetImageResizableUpdateFunc(
    ImageResizableSlice& resizable, const RefPtr<ResourceObject> resObj, ResizableOption direction)
{
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [direction](const RefPtr<ResourceObject>& currentResObj, ImageResizableSlice& slice) {
        CalcDimension dim;
        ResizableOption resizableOption;
        switch (direction) {
            case ResizableOption::LEFT:
                resizableOption = ResizableOption::LEFT;
                break;
            case ResizableOption::RIGHT:
                resizableOption = ResizableOption::RIGHT;
                break;
            case ResizableOption::TOP:
                resizableOption = ResizableOption::TOP;
                break;
            case ResizableOption::BOTTOM:
                resizableOption = ResizableOption::BOTTOM;
                break;
            default:
                return;
        }
        if (ResourceParseUtils::ParseResDimensionVpNG(currentResObj, dim) && dim.IsValid()) {
            slice.SetEdgeSlice(resizableOption, dim);
        }
    };
    switch (direction) {
        case ResizableOption::LEFT:
            resizable.AddResource("image.left", resObj, std::move(updateFunc));
            break;
        case ResizableOption::RIGHT:
            resizable.AddResource("image.right", resObj, std::move(updateFunc));
            break;
        case ResizableOption::TOP:
            resizable.AddResource("image.top", resObj, std::move(updateFunc));
            break;
        case ResizableOption::BOTTOM:
            resizable.AddResource("image.bottom", resObj, std::move(updateFunc));
            break;
        default:
            break;
    }
}

void SetResizableFromVec(ImageResizableSlice& resizable, const ArkUIStringAndFloat* options,
    std::vector<RefPtr<ResourceObject>>& imageResizableResArray)
{
    for (unsigned int index = 0; index < RESIZEABLE_VEC_LENGTH; index += NUM_3) {
        std::optional<CalcDimension> optDimension;
        SetCalcDimension(optDimension, options, RESIZEABLE_VEC_LENGTH, index);
        if (optDimension.has_value()) {
            auto direction = directions[index / NUM_3];
            if ((index / NUM_3) < imageResizableResArray.size()) {
                SetImageResizableUpdateFunc(resizable, imageResizableResArray[index / NUM_3], direction);
            }
            resizable.SetEdgeSlice(direction, optDimension.value());
        }
    }
}

void SetImageSrc(ArkUINodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string src(value);
    ImageModelNG::InitImage(frameNode, src);
}

const char* GetImageSrc(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = ImageModelNG::GetSrc(frameNode).GetSrc();
    return g_strValue.c_str();
}

RefPtr<ThemeConstants> GetThemeConstants(const char* bundleName, const char* moduleName)
{
    auto cardId = CardScope::CurrentId();
    if (cardId != INVALID_CARD_ID) {
        auto container = Container::Current();
        auto weak = container->GetCardPipeline(cardId);
        auto cardPipelineContext = weak.Upgrade();
        CHECK_NULL_RETURN(cardPipelineContext, nullptr);
        auto cardThemeManager = cardPipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(cardThemeManager, nullptr);
        return cardThemeManager->GetThemeConstants(bundleName, moduleName);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

void SetImageResource(
    ArkUINodeHandle node, int id, int type, const char* name, const char* bundleName, const char* moduleName)
{
    auto themeConstants = GetThemeConstants(bundleName, moduleName);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!themeConstants) {
        return;
    }
    std::optional<std::string> src;
    if (type == static_cast<int32_t>(ResourceType::RAWFILE)) {
        src = themeConstants->GetRawfile(name);
    }
    if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
        if (id == -1) {
            src = themeConstants->GetMediaPathByName(name);
        } else {
            src = themeConstants->GetMediaPath(id);
        }
    }
    if (!src.has_value()) {
        return;
    }

    ImageModelNG::InitImage(frameNode, src.value());
}

void SetCopyOption(ArkUINodeHandle node, ArkUI_Int32 copyOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = static_cast<CopyOptions>(copyOption);
    if (copyOptions < CopyOptions::None || copyOptions > CopyOptions::Distributed) {
        copyOptions = DEFAULT_IMAGE_COPYOPTION;
    }
    ImageModelNG::SetCopyOption(frameNode, copyOptions);
}

int32_t GetCopyOption(ArkUINodeHandle node)
{
    int32_t defaultCopyOption = static_cast<int32_t>(CopyOptions::None);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultCopyOption);
    return static_cast<int32_t>(ImageModelNG::GetCopyOption(frameNode));
}

void SetImageShowSrc(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName,
    ArkUI_Bool isUriPureNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetInitialSrc(frameNode, src, bundleName, moduleName, isUriPureNumber);
}

void SetImageShowSrcRes(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName,
    ArkUI_Bool isUriPureNumber, void* srcRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetInitialSrc(frameNode, src, bundleName, moduleName, isUriPureNumber);
    if (SystemProperties::ConfigChangePerform() && srcRawPtr) {
        auto* src = reinterpret_cast<ResourceObject*>(srcRawPtr);
        auto srcResObj = AceType::Claim(src);
        ImageModelNG::CreateWithResourceObj(frameNode, ImageResourceType::SRC, srcResObj);
    }
}

void ResetCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetCopyOption(frameNode, DEFAULT_IMAGE_COPYOPTION);
}

void SetAutoResize(ArkUINodeHandle node, ArkUI_Bool autoResize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAutoResize(frameNode, autoResize);
}

int32_t GetAutoResize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return ImageModelNG::GetAutoResize(frameNode);
}

void ResetAutoResize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetAutoResize(frameNode);
}

void SetObjectRepeat(ArkUINodeHandle node, ArkUI_Int32 imageRepeat)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto repeat = static_cast<ImageRepeat>(imageRepeat);
    if (repeat < ImageRepeat::NO_REPEAT || repeat > ImageRepeat::REPEAT) {
        repeat = ImageRepeat::NO_REPEAT;
    }
    ImageModelNG::SetImageRepeat(frameNode, repeat);
}

int32_t GetObjectRepeat(ArkUINodeHandle node)
{
    int32_t defaultObjectRepeat = static_cast<int32_t>(ImageRepeat::NO_REPEAT);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultObjectRepeat);
    return static_cast<int32_t>(ImageModelNG::GetObjectRepeat(frameNode));
}

void ResetObjectRepeat(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageRepeat(frameNode, ImageRepeat::NO_REPEAT);
}

void SetRenderMode(ArkUINodeHandle node, ArkUI_Int32 imageRenderMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto renderMode = static_cast<ImageRenderMode>(imageRenderMode);
    if (renderMode < ImageRenderMode::ORIGINAL || renderMode > ImageRenderMode::TEMPLATE) {
        renderMode = ImageRenderMode::ORIGINAL;
    }
    ImageModelNG::SetImageRenderMode(frameNode, renderMode);
}

void ResetRenderMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageRenderMode(frameNode, ImageRenderMode::ORIGINAL);
}

int32_t GetRenderMode(ArkUINodeHandle node)
{
    int32_t defaultRenderMode = static_cast<int32_t>(ImageRenderMode::ORIGINAL);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultRenderMode);
    return static_cast<int32_t>(ImageModelNG::GetImageRenderMode(frameNode));
}

void SetSyncLoad(ArkUINodeHandle node, ArkUI_Bool syncLoadValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, syncLoadValue);
}

void ResetSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, DEFAULT_SYNC_LOAD_VALUE);
}

int32_t GetSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return ImageModelNG::GetSyncLoad(frameNode);
}

void SetImageMatrix(ArkUINodeHandle node, const ArkUI_Float32* matrix)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Matrix4 matrix4Value = Matrix4(
        matrix[0], matrix[4], matrix[8], matrix[12],
        matrix[1], matrix[5], matrix[9], matrix[13],
        matrix[2], matrix[6], matrix[10], matrix[14],
        matrix[3], matrix[7], matrix[11], matrix[15]);
    ImageModelNG::SetImageMatrix(frameNode, matrix4Value);
}

void GetImageMatrix(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resizable = ImageModelNG::GetImageMatrix(frameNode);
    for (int32_t i = 0; i < size && i < resizable.Count(); ++i) {
        arrayValue[i] = resizable[i];
    }
}

void ResetImageMatrix(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    std::vector<float> matrix(matrix4Len);
    const int32_t initPosition = 5;
    for (int32_t i = 0; i < matrix4Len; i = i + initPosition) {
        matrix[i] = 1.0f;
    }
    Matrix4 defaultValue = Matrix4(
        matrix[0], matrix[4], matrix[8], matrix[12],
        matrix[1], matrix[5], matrix[9], matrix[13],
        matrix[2], matrix[6], matrix[10], matrix[14],
        matrix[3], matrix[7], matrix[11], matrix[15]);
    ImageModelNG::SetImageMatrix(frameNode, defaultValue);
}

void SetObjectFit(ArkUINodeHandle node, ArkUI_Int32 objectFitNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageFit objectFitValue = static_cast<ImageFit>(objectFitNumber);
    if (objectFitNumber == FIT_MATRIX) {
        objectFitValue = ImageFit::MATRIX;
    }
    ImageModelNG::SetImageFit(frameNode, objectFitValue);
}

int32_t GetObjectFit(ArkUINodeHandle node)
{
    int32_t defaultObjectFit = static_cast<int32_t>(ImageFit::COVER);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultObjectFit);
    return static_cast<int32_t>(ImageModelNG::GetObjectFit(frameNode));
}

void ResetObjectFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT_VALUE);
}

void SetFitOriginalSize(ArkUINodeHandle node, ArkUI_Bool fitOriginalSizeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, fitOriginalSizeValue);
}

void ResetFitOriginalSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, DEFAULT_FIT_ORIGINAL_SIZE);
}

void SetSourceSize(ArkUINodeHandle node, ArkUI_Float32 width, ArkUI_Float32 height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension widthObj(width, DimensionUnit::VP);
    CalcDimension heightObj(height, DimensionUnit::VP);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>(widthObj, heightObj));
}

void SetSourceSizeWithPX(ArkUINodeHandle node, ArkUI_Int32 width, ArkUI_Int32 height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension widthObj(width, DimensionUnit::PX);
    CalcDimension heightObj(height, DimensionUnit::PX);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>(widthObj, heightObj));
}

void ResetSourceSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>());
}

void GetSourceSize(ArkUINodeHandle node, ArkUI_Int32* arrayValue, ArkUI_Int32 size)
{
    CHECK_NULL_VOID(arrayValue);
    if (size != IMAGE_SOURCE_SIZE) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto sourceSize = ImageModelNG::GetImageSourceSize(frameNode);
    arrayValue[0] = static_cast<int32_t>(sourceSize.first.ConvertToPx());
    arrayValue[1] = static_cast<int32_t>(sourceSize.second.ConvertToPx());
}

void SetMatchTextDirection(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, static_cast<bool>(value));
}

int32_t GetMatchTextDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ImageModelNG::GetMatchTextDirection(frameNode);
}

void ResetMatchTextDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, false);
}

void SetFillColor(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFill(frameNode, Color(value));
}

void SetFillColorWithColorSpace(ArkUINodeHandle node, ArkUI_Uint32 value, ArkUI_Uint32 colorSpace, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFill(frameNode, Color(value, static_cast<ColorSpace>(colorSpace)));
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        ImageModelNG::CreateWithResourceObj(frameNode, ImageResourceType::FILL_COLOR, colorResObj);
    }
}

void ResetImageFill(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetImageFill(frameNode);
}

void ResetFillColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ImageTheme>();
    CHECK_NULL_VOID(theme);
    ImageModelNG::SetImageFill(frameNode, theme->GetFillColor());
}

void SetAlt(ArkUINodeHandle node, const char* src, const char* bundleName, const char* moduleName)
{
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return;
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAlt(frameNode, ImageSourceInfo { src, bundleName, moduleName });
}

void SetAltRes(ArkUINodeHandle node, const char* src, const char* bundleName, const char* moduleName, void* srcRawPtr)
{
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return;
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAlt(frameNode, ImageSourceInfo { src, bundleName, moduleName });
    if (SystemProperties::ConfigChangePerform() && srcRawPtr) {
        auto* src = reinterpret_cast<ResourceObject*>(srcRawPtr);
        auto srcResObj = AceType::Claim(src);
        ImageModelNG::CreateWithResourceObj(frameNode, ImageResourceType::ALT, srcResObj);
    }
}

const char* GetAlt(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = ImageModelNG::GetAlt(frameNode).GetSrc();
    return g_strValue.c_str();
}

void ResetAlt(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetImageAlt(frameNode);
}

void SetImageInterpolation(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto interpolation = static_cast<Ace::ImageInterpolation>(value);
    if (interpolation < Ace::ImageInterpolation::NONE || interpolation > Ace::ImageInterpolation::HIGH) {
        interpolation = Ace::ImageInterpolation::NONE;
    }
    ImageModelNG::SetImageInterpolation(frameNode, interpolation);
}

int32_t GetImageInterpolation(ArkUINodeHandle node)
{
    int32_t defaultInterpolation = static_cast<int32_t>(ImageInterpolation::NONE);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultInterpolation);
    return static_cast<int32_t>(ImageModelNG::GetInterpolation(frameNode));
}

void ResetImageInterpolation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetImageInterpolation(frameNode);
}

void SetColorFilter(ArkUINodeHandle node, const ArkUI_Float32* array, int length)
{
    CHECK_NULL_VOID(array);
    if (length != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, std::vector<float>(array, array + length));
}

void GetColorFilter(ArkUINodeHandle node, ArkUIFilterColorType* colorFilter)
{
    CHECK_NULL_VOID(colorFilter);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto filterFloatArray = ImageModelNG::GetColorFilter(frameNode);
    colorFilter->filterSize = filterFloatArray.size() < MAX_COLOR_FILTER_SIZE
                                  ? static_cast<int32_t>(filterFloatArray.size())
                                  : static_cast<int32_t>(MAX_COLOR_FILTER_SIZE);
    for (size_t i = 0; i < static_cast<size_t>(colorFilter->filterSize) && i < MAX_COLOR_FILTER_SIZE; i++) {
        *(colorFilter->filterArray+i) = filterFloatArray[i];
    }
}

void ResetColorFilter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, DEFAULT_COLOR_FILTER);
}

struct NativeHandle {
    std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter> value = nullptr;
};

// colorFilter must be OH_Drawing_ColorFilter NDK object
void SetDrawingColorFilter(ArkUINodeHandle node, void* colorFilter)
{
    CHECK_NULL_VOID(colorFilter);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto handle = reinterpret_cast<NativeHandle*>(colorFilter);
    auto filterPtr = handle->value;
    CHECK_NULL_VOID(filterPtr);
    auto drawingColorFilter = DrawingColorFilter::CreateDrawingColorFilterFromNative(static_cast<void*>(&filterPtr));
    ImageModelNG::SetDrawingColorFilter(frameNode, drawingColorFilter);
}

// return must be OH_Drawing_ColorFilter NDK object
void* GetDrawingColorFilter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto drawingColorFilter = ImageModelNG::GetDrawingColorFilter(frameNode);
    CHECK_NULL_RETURN(drawingColorFilter, nullptr);
    auto filterSptr = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter>*>(
        drawingColorFilter->GetDrawingColorFilterSptrAddr());
    CHECK_NULL_RETURN(filterSptr, nullptr);
    return reinterpret_cast<void*>(filterSptr);
}

void SetImageSyncLoad(ArkUINodeHandle node, ArkUI_Bool syncLoadValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, syncLoadValue);
}

void ResetImageSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, DEFAULT_SYNC_LOAD_VALUE);
}

void SetImageObjectFit(ArkUINodeHandle node, ArkUI_Int32 objectFitNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageFit objectFitValue = static_cast<ImageFit>(objectFitNumber);
    ImageModelNG::SetImageFit(frameNode, objectFitValue);
}

void ResetImageObjectFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT_VALUE);
}

void SetImageFitOriginalSize(ArkUINodeHandle node, ArkUI_Bool fitOriginalSizeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, fitOriginalSizeValue);
}

void ResetImageFitOriginalSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, DEFAULT_FIT_ORIGINAL_SIZE);
}

void SetImageDraggable(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, value);
}

void ResetImageDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, DEFAULT_DRAGGABLE);
}

int32_t GetImageDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_DRAGGABLE);
    return ImageModelNG::GetDraggable(frameNode);
}

/**
 * @param values radius values
 * value[0] : radius value for TopLeft，value[1] : radius value for TopRight
 * value[2] : radius value for BottomLeft，value[3] : radius value for BottomRight
 * @param units radius units
 * units[0]: radius unit for TopLeft ,units[1] : radius unit for TopRight
 * units[2]: radius unit for BottomLeft, units[3] : radius unit for TopRight
 */
void SetImageBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values, const int* units, ArkUI_Int32 length)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getCommonModifier()->setBorderRadius(node, values, units, length, nullptr);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        ImageModelNG::SetBackBorder(frameNode);
        return;
    }
    if (length != DEFAULT_LENGTH) {
        return;
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    borderRadius.multiValued = true;
    ImageModelNG::SetBorderRadius(frameNode, borderRadius);
}


void ResetImageBorderRadius(ArkUINodeHandle node)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getCommonModifier()->resetBorderRadius(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        ImageModelNG::SetBackBorder(frameNode);
        return;
    }
    OHOS::Ace::CalcDimension reset;
    ImageModelNG::SetBorderRadius(frameNode, reset);
}

void SetImageBorderWithValues(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesSize != NUM_12)) {
        return;
    }

    int32_t offset = NUM_0;
    NG::BorderRadiusProperty borderRadius;
    SetOptionalBorder(borderRadius.radiusTopLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusTopRight, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomRight, values, valuesSize, offset);

    borderRadius.multiValued = true;
    if (borderRadius.radiusTopLeft.has_value() || borderRadius.radiusTopRight.has_value() ||
        borderRadius.radiusBottomLeft.has_value() || borderRadius.radiusBottomRight.has_value()) {
        ImageModelNG::SetBorderRadius(frameNode, borderRadius);
    }
}

void SetImageBorder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetBackBorder(frameNode);
}

void ResetImageBorder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        ImageModelNG::SetBackBorder(frameNode);
        return;
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getCommonModifier()->resetBorder(node);
    CalcDimension borderRadius;
    ImageModelNG::SetBorderRadius(frameNode, borderRadius);
}

void SetImageOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opacityValue = static_cast<float>(opacity);
    if ((LessNotEqual(opacityValue, 0.0)) || GreatNotEqual(opacityValue, 1.0)) {
        opacityValue = 1.0f;
    }
    ViewAbstract::SetOpacity(frameNode, opacityValue);
}

void ResetImageOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

void SetEdgeAntialiasing(ArkUINodeHandle node, ArkUI_Float32 edgeAntialiasing)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSmoothEdge(frameNode, edgeAntialiasing);
}

void ResetEdgeAntialiasing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSmoothEdge(frameNode, DEFAULT_IMAGE_EDGE_ANTIALIASING);
}

void SetResizablePtr(ArkUINodeHandle node, const ArkUIStringAndFloat* options, void* imageResizablePtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<RefPtr<ResourceObject>> imageResizableResArray;
    if (imageResizablePtr != nullptr) {
        imageResizableResArray = *(static_cast<std::vector<RefPtr<ResourceObject>>*>(imageResizablePtr));
    }
    
    ImageResizableSlice resizable;
    SetResizableFromVec(resizable, options, imageResizableResArray);
    ImageModelNG::SetResizableSlice(frameNode, resizable);
}

void SetResizable(ArkUINodeHandle node, const ArkUIStringAndFloat* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SetResizablePtr(node, options, nullptr);
}

void ResetResizable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageResizableSlice defaultImageSlice;
    ImageModelNG::SetResizableSlice(frameNode, defaultImageSlice);
}

void SetResizableLattice(ArkUINodeHandle node, void* lattice)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto drawingLattice = DrawingLattice::CreateDrawingLattice(lattice);
    if (drawingLattice) {
        ImageModelNG::SetResizableLattice(frameNode, drawingLattice);
    } else {
        ImageModelNG::ResetResizableLattice(frameNode);
    }
}

void ResetResizableLattice(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetResizableLattice(frameNode);
}

void SetDynamicRangeMode(ArkUINodeHandle node, ArkUI_Int32 dynamicRangeMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DynamicRangeMode dynamicRangeModeValue = static_cast<DynamicRangeMode>(dynamicRangeMode);
    if (dynamicRangeModeValue < DynamicRangeMode::HIGH || dynamicRangeModeValue > DynamicRangeMode::STANDARD) {
        dynamicRangeModeValue = DynamicRangeMode::STANDARD;
    }
    ImageModelNG::SetDynamicRangeMode(frameNode, dynamicRangeModeValue);
}

int32_t GetDynamicRangeMode(ArkUINodeHandle node)
{
    int32_t defaultDynamicRangeMode = static_cast<int32_t>(DynamicRangeMode::STANDARD);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultDynamicRangeMode);
    return static_cast<int32_t>(ImageModelNG::GetDynamicRangeMode(frameNode));
}

void SetHdrBrightness(ArkUINodeHandle node, ArkUI_Float32 hdrBrightness)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (LessNotEqual(hdrBrightness, HDR_BRIGHTNESS_MIN) || GreatNotEqual(hdrBrightness, HDR_BRIGHTNESS_MAX)) {
        hdrBrightness = DEFAULT_HDR_BRIGHTNESS;
    }
    ImageModelNG::SetHdrBrightness(frameNode, hdrBrightness);
}

float GetHdrBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_HDR_BRIGHTNESS);
    return ImageModelNG::GetHdrBrightness(frameNode);
}

void ResetHdrBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetHdrBrightness(frameNode, HDR_BRIGHTNESS_MAX);
}

int32_t GetFitOriginalSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_FALSE);
    return ImageModelNG::GetFitOriginalSize(frameNode);
}

uint32_t GetFillColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ImageModelNG::GetFillColor(frameNode);
}

void SetPixelMap(ArkUINodeHandle node, void* drawableDescriptor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetPixelMap(frameNode, drawableDescriptor);
}

void SetPixelMapArray(ArkUINodeHandle node, void* animatedDrawableDescriptor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetPixelMapArray(frameNode, animatedDrawableDescriptor);
}

void SetResourceSrc(ArkUINodeHandle node, void* resource)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetResource(frameNode, resource);
}

void SetAltSourceInfo(ArkUINodeHandle node, const ArkUIImageSourceInfo* sourceInfo)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(sourceInfo);
    if (sourceInfo->url) {
        if (ImageSourceInfo::ResolveURIType(sourceInfo->url) == SrcType::NETWORK) {
            return;
        }
        ImageModelNG::SetAlt(frameNode, ImageSourceInfo { sourceInfo->url, "", "" });
        return;
    }
    if (sourceInfo->resource) {
        ImageModelNG::SetAltResource(frameNode, sourceInfo->resource);
        return;
    }
    if (sourceInfo->pixelMap) {
        ImageModelNG::SetAltPixelMap(frameNode, sourceInfo->pixelMap);
        return;
    }
}

void ResetDynamicRangeMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDynamicRangeMode(frameNode, DynamicRangeMode::STANDARD);
}

void SetEnhancedImageQuality(ArkUINodeHandle node, ArkUI_Int32 imageQuality)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    AIImageQuality imageQualityValue = static_cast<AIImageQuality>(imageQuality);
    if (imageQualityValue < AIImageQuality::NONE || imageQualityValue > AIImageQuality::HIGH) {
        imageQualityValue = AIImageQuality::NONE;
    }
    ImageModelNG::SetEnhancedImageQuality(frameNode, imageQualityValue);
}

void ResetEnhancedImageQuality(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetEnhancedImageQuality(frameNode, AIImageQuality::NONE);
}

void SetImageResizable(ArkUINodeHandle node, ArkUI_Float32 left, ArkUI_Float32 top,
    ArkUI_Float32 right, ArkUI_Float32 bottom)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageResizableSlice resizable;
    Dimension leftDimension(left, DimensionUnit::VP);
    resizable.SetEdgeSlice(ResizableOption::LEFT, leftDimension);
    Dimension topDimension(top, DimensionUnit::VP);
    resizable.SetEdgeSlice(ResizableOption::TOP, topDimension);
    Dimension rightDimension(right, DimensionUnit::VP);
    resizable.SetEdgeSlice(ResizableOption::RIGHT, rightDimension);
    Dimension bottomDimension(bottom, DimensionUnit::VP);
    resizable.SetEdgeSlice(ResizableOption::BOTTOM, bottomDimension);
    ImageModelNG::SetResizableSlice(frameNode, resizable);
}

void GetImageResizable(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resizable = ImageModelNG::GetResizableSlice(frameNode);
    if (0 < size) {
        arrayValue[0] = resizable.left.Value();
    }
    if (NUM_1 < size) {
        arrayValue[NUM_1] = resizable.top.Value();
    }
    if (NUM_2 < size) {
        arrayValue[NUM_2] = resizable.right.Value();
    }
    if (NUM_3 < size) {
        arrayValue[NUM_3] = resizable.bottom.Value();
    }
}

void EnableAnalyzer(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::EnableAnalyzer(frameNode, enable);
}

int32_t GetEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ImageModelNG::GetEnableAnalyzer(frameNode);
}

void ResetEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::EnableAnalyzer(frameNode, false);
}

void SetImagePrivacySensitve(ArkUINodeHandle node, ArkUI_Int32 sensitive)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(static_cast<bool>(sensitive));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ResetImagePrivacySensitve(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(DEFAULT_IMAGE_SENSITIVE);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void AnalyzerConfig(ArkUINodeHandle node, void* config)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageAnalyzerConfig(frameNode, config);
}

void ResetImageContent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetImage(frameNode);
}

void ResetImageSrc(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetImageSrc(frameNode);
}

void SetInitialPixelMap(ArkUINodeHandle node, ArkUI_Int64 pixelMap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    void* rawPtr = reinterpret_cast<void*>(pixelMap);
    CHECK_NULL_VOID(rawPtr);
    RefPtr<PixelMap> pixelMapRef = PixelMap::CreatePixelMap(rawPtr);
    ImageModelNG::SetInitialPixelMap(frameNode, pixelMapRef);
}

void SetOnComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onComplete = reinterpret_cast<std::function<void(const LoadImageSuccessEvent&)>*>(callback);
        ImageModelNG::SetOnComplete(frameNode, std::move(*onComplete));
    } else {
        ImageModelNG::SetOnComplete(frameNode, nullptr);
    }
}

void SetOnError(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const LoadImageFailEvent&)>*>(callback);
        ImageModelNG::SetOnError(frameNode, std::move(*onError));
    } else {
        ImageModelNG::SetOnError(frameNode, nullptr);
    }
}

void ResetOnError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOnError(frameNode, nullptr);
}

void SetImageOnFinish(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onFinish = reinterpret_cast<std::function<void()>*>(callback);
        ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(*onFinish));
    } else {
        ImageModelNG::SetOnSvgPlayFinish(frameNode, nullptr);
    }
}

void ResetImageOnFinish(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOnSvgPlayFinish(frameNode, nullptr);
}

void SetImageRotateOrientation(ArkUINodeHandle node, ArkUI_Int32 orientation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto orientationValue = static_cast<ImageRotateOrientation>(orientation);
    if (orientationValue < ImageRotateOrientation::AUTO || orientationValue > ImageRotateOrientation::LEFT_MIRRORED) {
        orientationValue = ImageRotateOrientation::UP;
    }
    ImageModelNG::SetOrientation(frameNode, orientationValue);
}

int32_t GetImageRotateOrientation(ArkUINodeHandle node)
{
    int32_t defaultImageRotateOrientation = static_cast<int32_t>(ImageRotateOrientation::UP);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultImageRotateOrientation);
    return static_cast<int32_t>(ImageModelNG::GetOrientation(frameNode));
}

void ResetImageRotateOrientation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOrientation(frameNode, ImageRotateOrientation::UP);
}

void SetSupportSvg2(ArkUINodeHandle node, ArkUI_Bool supportSvg2)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSupportSvg2(frameNode, supportSvg2);
}

void ResetSupportSvg2(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetSupportSvg2(frameNode);
}

int32_t GetSupportSvg2(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ImageModelNG::GetSupportSvg2(frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUIImageModifier* GetImageModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIImageModifier modifier = {
        .setSrc = SetImageSrc,
        .setImageShowSrc = SetImageShowSrc,
        .setImageShowSrcRes = SetImageShowSrcRes,
        .setImageResource = SetImageResource,
        .setCopyOption = SetCopyOption,
        .resetCopyOption = ResetCopyOption,
        .setAutoResize = SetAutoResize,
        .resetAutoResize = ResetAutoResize,
        .setObjectRepeat = SetObjectRepeat,
        .resetObjectRepeat = ResetObjectRepeat,
        .setRenderMode = SetRenderMode,
        .resetRenderMode = ResetRenderMode,
        .setSyncLoad = SetSyncLoad,
        .resetSyncLoad = ResetSyncLoad,
        .setImageMatrix = SetImageMatrix,
        .resetImageMatrix = ResetImageMatrix,
        .setObjectFit = SetObjectFit,
        .resetObjectFit = ResetObjectFit,
        .setFitOriginalSize = SetFitOriginalSize,
        .resetFitOriginalSize = ResetFitOriginalSize,
        .setSourceSize = SetSourceSize,
        .setSourceSizeWithPX = SetSourceSizeWithPX,
        .resetSourceSize = ResetSourceSize,
        .setMatchTextDirection = SetMatchTextDirection,
        .resetMatchTextDirection = ResetMatchTextDirection,
        .setFillColor = SetFillColor,
        .setFillColorWithColorSpace = SetFillColorWithColorSpace,
        .resetImageFill = ResetImageFill,
        .resetFillColor = ResetFillColor,
        .setAlt = SetAlt,
        .setAltRes = SetAltRes,
        .resetAlt = ResetAlt,
        .setImageInterpolation = SetImageInterpolation,
        .resetImageInterpolation = ResetImageInterpolation,
        .setColorFilter = SetColorFilter,
        .resetColorFilter = ResetColorFilter,
        .setImageSyncLoad = SetImageSyncLoad,
        .resetImageSyncLoad = ResetImageSyncLoad,
        .setImageObjectFit = SetImageObjectFit,
        .resetImageObjectFit = ResetImageObjectFit,
        .setImageFitOriginalSize = SetImageFitOriginalSize,
        .resetImageFitOriginalSize = ResetImageFitOriginalSize,
        .setImageDraggable = SetImageDraggable,
        .resetImageDraggable = ResetImageDraggable,
        .setImageBorderRadius = SetImageBorderRadius,
        .resetImageBorderRadius = ResetImageBorderRadius,
        .setImageBorder = SetImageBorder,
        .setImageBorderWithValues = SetImageBorderWithValues,
        .resetImageBorder = ResetImageBorder,
        .setImageOpacity = SetImageOpacity,
        .resetImageOpacity = ResetImageOpacity,
        .setEdgeAntialiasing = SetEdgeAntialiasing,
        .resetEdgeAntialiasing = ResetEdgeAntialiasing,
        .setResizablePtr = SetResizablePtr,
        .setResizable = SetResizable,
        .resetResizable = ResetResizable,
        .setDynamicRangeMode = SetDynamicRangeMode,
        .resetDynamicRangeMode = ResetDynamicRangeMode,
        .setHdrBrightness = SetHdrBrightness,
        .resetHdrBrightness = ResetHdrBrightness,
        .setImageRotateOrientation = SetImageRotateOrientation,
        .resetImageRotateOrientation = ResetImageRotateOrientation,
        .setEnhancedImageQuality = SetEnhancedImageQuality,
        .resetEnhancedImageQuality = ResetEnhancedImageQuality,
        .getImageSrc = GetImageSrc,
        .getAutoResize = GetAutoResize,
        .getSyncLoad = GetSyncLoad,
        .getObjectRepeat = GetObjectRepeat,
        .getObjectFit = GetObjectFit,
        .getImageInterpolation = GetImageInterpolation,
        .getImageRotateOrientation = GetImageRotateOrientation,
        .getHdrBrightness = GetHdrBrightness,
        .getDynamicRangeMode = GetDynamicRangeMode,
        .getEnableAnalyzer = GetEnableAnalyzer,
        .getCopyOption = GetCopyOption,
        .getMatchTextDirection = GetMatchTextDirection,
        .getImageMatrix = GetImageMatrix,
        .getSourceSize = GetSourceSize,
        .getColorFilter = GetColorFilter,
        .getAlt = GetAlt,
        .getImageDraggable = GetImageDraggable,
        .getRenderMode = GetRenderMode,
        .setImageResizable = SetImageResizable,
        .getImageResizable = GetImageResizable,
        .getFitOriginalSize = GetFitOriginalSize,
        .getFillColor = GetFillColor,
        .setPixelMap = SetPixelMap,
        .setPixelMapArray = SetPixelMapArray,
        .setResourceSrc = SetResourceSrc,
        .enableAnalyzer = EnableAnalyzer,
        .resetEnableAnalyzer = ResetEnableAnalyzer,
        .setImagePrivacySensitive = SetImagePrivacySensitve,
        .resetImagePrivacySensitive = ResetImagePrivacySensitve,
        .analyzerConfig = AnalyzerConfig,
        .setDrawingColorFilter = SetDrawingColorFilter,
        .getDrawingColorFilter = GetDrawingColorFilter,
        .resetImageContent = ResetImageContent,
        .resetImageSrc = ResetImageSrc,
        .setInitialPixelMap = SetInitialPixelMap,
        .setAltSourceInfo = SetAltSourceInfo,
        .setOnComplete = SetOnComplete,
        .setOnError = SetOnError,
        .resetOnError = ResetOnError,
        .setImageOnFinish = SetImageOnFinish,
        .resetImageOnFinish = ResetImageOnFinish,
        .setResizableLattice = SetResizableLattice,
        .resetResizableLattice = ResetResizableLattice,
        .setSupportSvg2 = SetSupportSvg2,
        .resetSupportSvg2 = ResetSupportSvg2,
        .getSupportSvg2 = GetSupportSvg2,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIImageModifier* GetCJUIImageModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIImageModifier modifier = {
        .setSrc = SetImageSrc,
        .setImageShowSrc = SetImageShowSrc,
        .setImageShowSrcRes = SetImageShowSrcRes,
        .setCopyOption = SetCopyOption,
        .resetCopyOption = ResetCopyOption,
        .setAutoResize = SetAutoResize,
        .resetAutoResize = ResetAutoResize,
        .setObjectRepeat = SetObjectRepeat,
        .resetObjectRepeat = ResetObjectRepeat,
        .setRenderMode = SetRenderMode,
        .resetRenderMode = ResetRenderMode,
        .setSyncLoad = SetSyncLoad,
        .resetSyncLoad = ResetSyncLoad,
        .setImageMatrix = SetImageMatrix,
        .resetImageMatrix = ResetImageMatrix,
        .setObjectFit = SetObjectFit,
        .resetObjectFit = ResetObjectFit,
        .setFitOriginalSize = SetFitOriginalSize,
        .resetFitOriginalSize = ResetFitOriginalSize,
        .setSourceSize = SetSourceSize,
        .setSourceSizeWithPX = SetSourceSizeWithPX,
        .resetSourceSize = ResetSourceSize,
        .setMatchTextDirection = SetMatchTextDirection,
        .resetMatchTextDirection = ResetMatchTextDirection,
        .setFillColor = SetFillColor,
        .setFillColorWithColorSpace = SetFillColorWithColorSpace,
        .resetFillColor = ResetFillColor,
        .setAlt = SetAlt,
        .setAltRes = SetAltRes,
        .resetAlt = ResetAlt,
        .setImageInterpolation = SetImageInterpolation,
        .resetImageInterpolation = ResetImageInterpolation,
        .setColorFilter = SetColorFilter,
        .resetColorFilter = ResetColorFilter,
        .setImageSyncLoad = SetImageSyncLoad,
        .resetImageSyncLoad = ResetImageSyncLoad,
        .setImageObjectFit = SetImageObjectFit,
        .resetImageObjectFit = ResetImageObjectFit,
        .setImageFitOriginalSize = SetImageFitOriginalSize,
        .resetImageFitOriginalSize = ResetImageFitOriginalSize,
        .setImageDraggable = SetImageDraggable,
        .resetImageDraggable = ResetImageDraggable,
        .setImageBorderRadius = SetImageBorderRadius,
        .resetImageBorderRadius = ResetImageBorderRadius,
        .setImageBorder = SetImageBorder,
        .resetImageBorder = ResetImageBorder,
        .setImageOpacity = SetImageOpacity,
        .resetImageOpacity = ResetImageOpacity,
        .setEdgeAntialiasing = SetEdgeAntialiasing,
        .resetEdgeAntialiasing = ResetEdgeAntialiasing,
        .setResizablePtr = SetResizablePtr,
        .setResizable = SetResizable,
        .resetResizable = ResetResizable,
        .setDynamicRangeMode = SetDynamicRangeMode,
        .resetDynamicRangeMode = ResetDynamicRangeMode,
        .setEnhancedImageQuality = SetEnhancedImageQuality,
        .resetEnhancedImageQuality = ResetEnhancedImageQuality,
        .getImageSrc = GetImageSrc,
        .getAutoResize = GetAutoResize,
        .getSyncLoad = GetSyncLoad,
        .getObjectRepeat = GetObjectRepeat,
        .getObjectFit = GetObjectFit,
        .getImageInterpolation = GetImageInterpolation,
        .getImageRotateOrientation = GetImageRotateOrientation,
        .getHdrBrightness = GetHdrBrightness,
        .getDynamicRangeMode = GetDynamicRangeMode,
        .getEnableAnalyzer = GetEnableAnalyzer,
        .getCopyOption = GetCopyOption,
        .getMatchTextDirection = GetMatchTextDirection,
        .getImageMatrix = GetImageMatrix,
        .getSourceSize = GetSourceSize,
        .getColorFilter = GetColorFilter,
        .getAlt = GetAlt,
        .getImageDraggable = GetImageDraggable,
        .getRenderMode = GetRenderMode,
        .setImageResizable = SetImageResizable,
        .getImageResizable = GetImageResizable,
        .getFitOriginalSize = GetFitOriginalSize,
        .getFillColor = GetFillColor,
        .setPixelMap = SetPixelMap,
        .setPixelMapArray = SetPixelMapArray,
        .setResourceSrc = SetResourceSrc,
        .enableAnalyzer = EnableAnalyzer,
        .resetEnableAnalyzer = ResetEnableAnalyzer,
        .setImagePrivacySensitive = SetImagePrivacySensitve,
        .resetImagePrivacySensitive = ResetImagePrivacySensitve,
        .analyzerConfig = AnalyzerConfig,
        .setDrawingColorFilter = SetDrawingColorFilter,
        .getDrawingColorFilter = GetDrawingColorFilter,
        .resetImageSrc = ResetImageSrc,
        .setInitialPixelMap = SetInitialPixelMap,
        .setOnComplete = SetOnComplete,
        .setOnError = SetOnError,
        .resetOnError = ResetOnError,
        .setImageOnFinish = SetImageOnFinish,
        .resetImageOnFinish = ResetImageOnFinish,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetImageOnComplete(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const LoadImageSuccessEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_COMPLETE;
        event.componentAsyncEvent.data[IMAGE_LOAD_STATUS_INDEX].i32 = info.GetLoadingStatus();
        event.componentAsyncEvent.data[IMAGE_WIDTH_INDEX].f32 = info.GetWidth();
        event.componentAsyncEvent.data[IMAGE_HEIGHT_INDEX].f32 = info.GetHeight();
        event.componentAsyncEvent.data[IMAGE_COMPONENT_WIDTH_INDEX].f32 = info.GetComponentWidth();
        event.componentAsyncEvent.data[IMAGE_COMPONENT_HEIGHT_INDEX].f32 = info.GetComponentHeight();
        event.componentAsyncEvent.data[IMAGE_CONTENT_OFFSET_X_INDEX].f32 = info.GetContentOffsetX();
        event.componentAsyncEvent.data[IMAGE_CONTENT_OFFSET_Y_INDEX].f32 = info.GetContentOffsetY();
        event.componentAsyncEvent.data[IMAGE_CONTENT_WIDTH_INDEX].f32 = info.GetContentWidth();
        event.componentAsyncEvent.data[IMAGE_CONTENT_HEIGHT_INDEX].f32 = info.GetContentHeight();
        SendArkUISyncEvent(&event);
    };
    ImageModelNG::SetOnComplete(frameNode, std::move(onEvent));
}

void SetImageOnError(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const LoadImageFailEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_ERROR;
        event.componentAsyncEvent.data[0].i32 = LOAD_ERROR_CODE;
        SendArkUISyncEvent(&event);
    };
    ImageModelNG::SetOnError(frameNode, std::move(onEvent));
}

void SetImageOnSvgPlayFinish(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSvgPlayFinishEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_SVG_PLAY_FINISH;
        SendArkUISyncEvent(&event);
    };
    ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(onSvgPlayFinishEvent));
}

void SetImageOnDownloadProgress(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDownloadProgress = [node, extraParam](const uint32_t& dlNow, const uint32_t& dlTotal) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_DOWNLOAD_PROGRESS;
        event.componentAsyncEvent.data[0].u32 = dlNow;
        event.componentAsyncEvent.data[1].u32 = dlTotal;
        SendArkUISyncEvent(&event);
    };
    ImageModelNG::SetOnDownloadProgress(frameNode, std::move(onDownloadProgress));
}

void ResetImageOnComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOnComplete(frameNode, nullptr);
}
void ResetImageOnError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOnError(frameNode, nullptr);
}
void ResetImageOnSvgPlayFinish(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOnSvgPlayFinish(frameNode, nullptr);
}
void ResetImageOnDownloadProgress(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetOnDownloadProgress(frameNode, nullptr);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

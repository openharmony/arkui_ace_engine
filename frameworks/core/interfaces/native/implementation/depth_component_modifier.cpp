/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components/common/properties/depth_option.h"
#include "core/components_ng/pattern/depth_component/depth_component_model.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace {
constexpr uint32_t NUM_4 = 4;
constexpr uint32_t NUM_5 = 5;
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DepthComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = DepthComponentModel::CreateFrameNode(id, OHOS::Ace::DepthBackgroundSource());
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // DepthComponentModifier

namespace {
bool IsGltfSource(const std::string& src)
{
    if (src.empty()) {
        return false;
    }
    auto queryPos = src.find('?');
    std::string cleanSrc = (queryPos == std::string::npos) ? src : src.substr(0, queryPos);
    if (cleanSrc.size() <= NUM_5) {
        return false;
    }
    std::transform(cleanSrc.begin(), cleanSrc.end(), cleanSrc.begin(), ::tolower);
    return cleanSrc.rfind(".gltf") == cleanSrc.size() - NUM_5 || cleanSrc.rfind(".glb") == cleanSrc.size() - NUM_4;
}

bool SetOhosPath(const std::string& uri, std::string& ohosPath)
{
    if (uri.empty()) {
        return false;
    }
    const std::string resourceRawUriPrefix = "resource://RAWFILE/";
    const std::string ohosRawfilePrefix = "OhosRawFile://";
    const std::string resourceUriPrefix = "resource:///";
    const std::string filePrefix = "file://";

    if (uri.find(resourceRawUriPrefix) == 0) {
        ohosPath = ohosRawfilePrefix + uri.substr(resourceRawUriPrefix.size());
        return true;
    }
    if (uri.find(ohosRawfilePrefix) == 0 || uri.find(filePrefix) == 0 ||
        uri.find(resourceUriPrefix) == 0) {
        ohosPath = uri;
        return true;
    }
    ohosPath = filePrefix + uri;
    return true;
}

OHOS::Ace::DepthBackgroundSource ParseBackgroundFromSource(const std::string& src,
    const std::string& bundleName = {}, const std::string& moduleName = {})
{
    if (IsGltfSource(src)) {
        std::string ohosPath;
        if (SetOhosPath(src, ohosPath)) {
            return OHOS::Ace::DepthBackgroundSource::CreateGltf(ohosPath, src, bundleName, moduleName);
        }
    }
    return OHOS::Ace::DepthBackgroundSource::CreateImage(
        ImageSourceInfo(src, bundleName, moduleName), src, bundleName, moduleName);
}
} // namespace

namespace DepthComponentInterfaceModifier {
void SetDepthComponentOptionsImpl(Ark_NativePointer node,
                                  const Ark_Union_ResourceStr_image_PixelMap* background,
                                  const Opt_DepthComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(background);
    std::optional<OHOS::Ace::DepthBackgroundSource> bgSource;
    Converter::VisitUnion(*background,
        [&bgSource](const Ark_ResourceStr& value) {
            Converter::VisitUnion(value,
                [&bgSource](const Ark_String& v) {
                    auto src = Converter::OptConvert<std::string>(v);
                    if (src) {
                        bgSource = ParseBackgroundFromSource(*src);
                    }
                },
                [&bgSource](const Ark_Resource& v) {
                    Converter::ResourceConverter converter(v);
                    auto src = converter.ToString();
                    if (src) {
                        bgSource = ParseBackgroundFromSource(
                            *src, converter.BundleName(), converter.ModuleName());
                    }
                },
                []() {});
        },
        [&bgSource](const Ark_image_PixelMap& value) {
            auto info = Converter::OptConvert<ImageSourceInfo>(value);
            if (info) {
                bgSource = OHOS::Ace::DepthBackgroundSource::CreateImage(*info);
            }
        },
        []() {});
    DepthComponentModel::SetBackgroundSource(frameNode,
        bgSource.value_or(OHOS::Ace::DepthBackgroundSource()));
    if (options && options->tag != INTEROP_TAG_UNDEFINED) {
        auto depthSpace = Converter::OptConvert<OHOS::Ace::DepthSpaceType>(options->value.depthSpace);
        if (depthSpace) {
            DepthComponentModel::SetDepthSpace(frameNode, *depthSpace);
        }
    }
}
} // DepthComponentInterfaceModifier

namespace DepthComponentAttributeModifier {
void SetDepthMapImpl(Ark_NativePointer node,
                     const Ark_Union_ResourceStr_image_PixelMap* value,
                     const Opt_DepthMapCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto applyDepthMap = [frameNode, callback](const ImageSourceInfo& info) {
        auto cb = Converter::GetOptPtr(callback);
        if (cb) {
            auto arkCallback = CallbackHelper(*cb);
            auto onError = [arkCallback](int32_t errorCode, const std::string& errorMessage) {
                Ark_BusinessErrorInterface_Void err = {};
                err.code = Converter::ArkValue<Ark_Int32>(errorCode);
                err.message = Converter::ArkValue<Ark_String>(errorMessage);
                arkCallback.InvokeSync(err);
            };
            DepthComponentModel::SetDepthMap(frameNode, info, std::move(onError));
        } else {
            DepthComponentModel::SetDepthMap(frameNode, info);
        }
    };
    Converter::VisitUnion(*value,
        [&applyDepthMap](const Ark_ResourceStr& v) {
            Converter::VisitUnion(v,
                [&applyDepthMap](const Ark_String& s) {
                    auto info = Converter::OptConvert<ImageSourceInfo>(s);
                    if (info) {
                        applyDepthMap(*info);
                    }
                },
                [&applyDepthMap](const Ark_Resource& r) {
                    auto info = Converter::OptConvert<ImageSourceInfo>(r);
                    if (info) {
                        applyDepthMap(*info);
                    }
                },
                []() {});
        },
        [&applyDepthMap](const Ark_image_PixelMap& v) {
            auto info = Converter::OptConvert<ImageSourceInfo>(v);
            if (info) {
                applyDepthMap(*info);
            }
        },
        [&applyDepthMap]() { applyDepthMap(ImageSourceInfo()); });
}

void SetCameraImpl(Ark_NativePointer node,
                   const Ark_DepthCameraParams* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto camera = Converter::OptConvert<OHOS::Ace::DepthCameraParams>(*value);
    if (camera) {
        if (!camera->cameraBufferCrop) {
            OHOS::Ace::CameraBufferCrop defaultCrop;
            auto geoNode = frameNode->GetGeometryNode();
            if (geoNode) {
                defaultCrop.bufferWidth = static_cast<int32_t>(geoNode->GetFrameSize().Width());
                defaultCrop.bufferHeight = static_cast<int32_t>(geoNode->GetFrameSize().Height());
            }
            defaultCrop.cropOffset = {0.0f, 0.0f};
            defaultCrop.cropScale = 1.0f;
            camera->cameraBufferCrop = defaultCrop;
        }
        DepthComponentModel::SetCamera(frameNode, *camera);
    }
}

void SetLightImpl(Ark_NativePointer node,
                  const Ark_DepthLightParams* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto light = Converter::OptConvert<OHOS::Ace::DepthLightParams>(*value);
    if (light) {
        DepthComponentModel::SetLight(frameNode, *light);
    }
}

void SetOnCompleteImpl(Ark_NativePointer node,
                       const DepthComponentCompleteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value) {
        DepthComponentModel::SetOnComplete(frameNode, nullptr);
        return;
    }
    auto onComplete = [arkCallback = CallbackHelper(*value)](
                          const DepthComponentCompleteEvent& event) {
        Ark_DepthComponentCompleteEvent arkEvent = {};
        arkEvent.componentWidth = Converter::ArkValue<Ark_Float64>(event.componentWidth);
        arkEvent.componentHeight = Converter::ArkValue<Ark_Float64>(event.componentHeight);
        arkCallback.InvokeSync(arkEvent);
    };
    DepthComponentModel::SetOnComplete(frameNode, std::move(onComplete));
}

void SetOnErrorImpl(Ark_NativePointer node,
                    const DepthComponentErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value) {
        DepthComponentModel::SetOnError(frameNode, nullptr);
        return;
    }
    auto onError = [arkCallback = CallbackHelper(*value)](
                       const DepthComponentErrorEvent& event) {
        Ark_DepthComponentErrorEvent arkEvent = {};
        arkEvent.componentWidth = Converter::ArkValue<Ark_Float64>(event.componentWidth);
        arkEvent.componentHeight = Converter::ArkValue<Ark_Float64>(event.componentHeight);
        Ark_BusinessErrorInterface_Void error = {};
        error.code = Converter::ArkValue<Ark_Int32>(event.errorCode);
        error.message = Converter::ArkValue<Ark_String>(event.errorMessage);
        arkEvent.error = Converter::ArkValue<Opt_BusinessErrorInterface_Void>(error);
        arkCallback.InvokeSync(arkEvent);
    };
    DepthComponentModel::SetOnError(frameNode, std::move(onError));
}
} // DepthComponentAttributeModifier

const GENERATED_ArkUIDepthComponentModifier* GetDepthComponentModifier()
{
    static const GENERATED_ArkUIDepthComponentModifier ArkUIDepthComponentModifierImpl {
        DepthComponentModifier::ConstructImpl,
        DepthComponentInterfaceModifier::SetDepthComponentOptionsImpl,
        DepthComponentAttributeModifier::SetCameraImpl,
        DepthComponentAttributeModifier::SetLightImpl,
        DepthComponentAttributeModifier::SetOnCompleteImpl,
        DepthComponentAttributeModifier::SetOnErrorImpl,
        DepthComponentAttributeModifier::SetDepthMapImpl,
    };
    return &ArkUIDepthComponentModifierImpl;
}
}

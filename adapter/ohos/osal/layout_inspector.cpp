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

#include "core/common/layout_inspector.h"

#include "include/core/SkImage.h"
#include "include/core/SkString.h"
#include "include/utils/SkBase64.h"

#include "connect_server_manager.h"

#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "adapter/ohos/entrance/subwindow/subwindow_ohos.h"
#include "base/thread/background_task_executor.h"
#include "core/common/ace_engine.h"
#include "core/common/connect_server_manager.h"
#include "core/components_v2/inspector/inspector.h"

namespace OHOS::Ace {

namespace {

sk_sp<SkColorSpace> ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return SkColorSpace::MakeSRGB();
}

SkAlphaType AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return SkAlphaType::kUnknown_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return SkAlphaType::kOpaque_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return SkAlphaType::kPremul_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return SkAlphaType::kUnpremul_SkAlphaType;
        default:
            return SkAlphaType::kUnknown_SkAlphaType;
    }
}

SkColorType PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return SkColorType::kRGB_565_SkColorType;
        case PixelFormat::RGBA_8888:
            return SkColorType::kRGBA_8888_SkColorType;
        case PixelFormat::BGRA_8888:
            return SkColorType::kBGRA_8888_SkColorType;
        case PixelFormat::ALPHA_8:
            return SkColorType::kAlpha_8_SkColorType;
        case PixelFormat::RGBA_F16:
            return SkColorType::kRGBA_F16_SkColorType;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return SkColorType::kUnknown_SkColorType;
    }
}

SkImageInfo MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    SkColorType colorType = PixelFormatToSkColorType(pixmap);
    SkAlphaType alphaType = AlphaTypeToSkAlphaType(pixmap);
    sk_sp<SkColorSpace> colorSpace = ColorSpaceToSkColorSpace(pixmap);
    return SkImageInfo::Make(pixmap->GetWidth(), pixmap->GetHeight(), colorType, alphaType, colorSpace);
}

const OHOS::sptr<OHOS::Rosen::Window> GetWindow(int32_t containerId)
{
    auto container = AceEngine::Get().GetContainer(containerId);
    if (containerId >= MIN_SUBCONTAINER_ID && containerId < MIN_PLUGIN_SUBCONTAINER_ID) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(
            SubwindowManager::GetInstance()->GetParentContainerId(containerId));
        CHECK_NULL_RETURN(subwindow, nullptr);
        if (AceType::InstanceOf<SubwindowOhos>(subwindow)) {
            auto subWindowOhos = AceType::DynamicCast<SubwindowOhos>(subwindow);
            CHECK_NULL_RETURN(subWindowOhos, nullptr);
            return subWindowOhos->GetSubWindow();
        }
    } else {
        auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
        if (aceContainer != nullptr) {
            return OHOS::Rosen::Window::Find(aceContainer->GetWindowName());
        }
        return OHOS::Rosen::Window::GetTopWindowWithId(container->GetWindowId());
    }
    return nullptr;
}
} // namespace

constexpr static char RECNODE_SELFID[] = "selfId";
constexpr static char RECNODE_NODEID[] = "nodeID";
constexpr static char RECNODE_NAME[] = "value";
constexpr static char RECNODE_DEBUGLINE[] = "debugLine";
constexpr static char RECNODE_CHILDREN[] = "RSNode";
constexpr static char ARK_DEBUGGER_LIB_PATH[] = "libark_connect_inspector.z.so";

bool LayoutInspector::stateProfilerStatus_ = false;
bool LayoutInspector::layoutInspectorStatus_ = false;
bool LayoutInspector::isUseStageModel_ = false;
std::mutex LayoutInspector::recMutex_;
ProfilerStatusCallback LayoutInspector::jsStateProfilerStatusCallback_ = nullptr;
RsProfilerNodeMountCallback LayoutInspector::rsProfilerNodeMountCallback_ = nullptr;
const char PNG_TAG[] = "png";
NG::InspectorTreeMap LayoutInspector::recNodeInfos_;
std::once_flag LayoutInspector::loadFlag;
void* LayoutInspector::handlerConnectServerSo = nullptr;
LayoutInspector::SetArkUICallback LayoutInspector::setArkUICallback = nullptr;

void LayoutInspector::SupportInspector()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (!layoutInspectorStatus_) {
        return;
    }
    std::string treeJsonStr;
    GetInspectorTreeJsonStr(treeJsonStr, ContainerScope::CurrentId());
    if (treeJsonStr.empty()) {
        return;
    }
    auto message = JsonUtil::Create(true);
    GetSnapshotJson(ContainerScope::CurrentId(), message);
    CHECK_NULL_VOID(message);

    auto sendTask = [treeJsonStr, jsonSnapshotStr = message->ToString(), container]() {
        if (container->IsUseStageModel()) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        } else {
            OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendTask));
}

void LayoutInspector::SetStatus(bool layoutInspectorStatus)
{
    layoutInspectorStatus_ = layoutInspectorStatus;
}

void LayoutInspector::TriggerJsStateProfilerStatusCallback(bool status)
{
    if (jsStateProfilerStatusCallback_) {
        stateProfilerStatus_ = status;
        jsStateProfilerStatusCallback_(status);
    }
}

void LayoutInspector::SetJsStateProfilerStatusCallback(ProfilerStatusCallback&& callback)
{
    jsStateProfilerStatusCallback_ = callback;
}

bool LayoutInspector::GetStateProfilerStatus()
{
    return stateProfilerStatus_;
}

RsProfilerNodeMountCallback LayoutInspector::GetRsProfilerNodeMountCallback()
{
    return rsProfilerNodeMountCallback_;
}

void LayoutInspector::SetRsProfilerNodeMountCallback(RsProfilerNodeMountCallback&& callback)
{
    rsProfilerNodeMountCallback_ = callback;
}

void LayoutInspector::SendStateProfilerMessage(const std::string& message)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().SendStateProfilerMessage(message);
}

void LayoutInspector::SetStateProfilerStatus(bool status)
{
    auto taskExecutor = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [status]() { LayoutInspector::TriggerJsStateProfilerStatusCallback(status); };
    taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI, "ArkUISetStateProfilerStatus");
}

void LayoutInspector::ConnectServerCallback()
{
    TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "connect server callback isStage:%{public}d", isUseStageModel_);
    if (isUseStageModel_) {
        TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "connect server, reset callback.");
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetRecordCallback(
            LayoutInspector::HandleStartRecord, LayoutInspector::HandleStopRecord);
    }
}

void LayoutInspector::SetCallback(int32_t instanceId)
{
    TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "InstanceId:%{public}d", instanceId);
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    if (container->IsUseStageModel()) {
        AddInstanceCallBack addInstanceCallBack = [](int32_t id) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SetProfilerCallBack(
                [](bool status) { return SetStateProfilerStatus(status); });
            OHOS::AbilityRuntime::ConnectServerManager::Get().SetSwitchCallback(
                [](bool status) { return SetStatus(status); },
                [](int32_t containerId) { return CreateLayoutInfo(containerId); }, id);
        };
        OHOS::AbilityRuntime::ConnectServerManager::Get().RegisterAddInstanceCallback(addInstanceCallBack);
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetRecordCallback(
            LayoutInspector::HandleStartRecord, LayoutInspector::HandleStopRecord);
        OHOS::AbilityRuntime::ConnectServerManager::Get().RegisterConnectServerCallback(
            LayoutInspector::ConnectServerCallback);
        isUseStageModel_ = true;
        RegisterConnectCallback();
    } else {
        OHOS::Ace::ConnectServerManager::Get().SetLayoutInspectorCallback(
            [](int32_t containerId) { return CreateLayoutInfo(containerId); },
            [](bool status) { return SetStatus(status); });
        isUseStageModel_ = false;
    }

    SendInstanceMessageCallBack sendInstanceMessageCallBack = [](int32_t id) {
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetProfilerCallBack(
            [](bool status) { return SetStateProfilerStatus(status); });
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetSwitchCallback(
            [](bool status) { return SetStatus(status); },
            [](int32_t containerId) { return CreateLayoutInfo(containerId); }, id);
    };
    OHOS::AbilityRuntime::ConnectServerManager::Get().RegisterSendInstanceMessageCallback(sendInstanceMessageCallBack);
}

void LayoutInspector::CreateContainerLayoutInfo(RefPtr<Container>& container)
{
    CHECK_NULL_VOID(container);
    if (container->IsDynamicRender()) {
        container = Container::CurrentSafely();
        CHECK_NULL_VOID(container);
    }
    int32_t containerId = container->GetInstanceId();
    ContainerScope socpe(containerId);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto getInspectorTask = [container, containerId]() {
        std::string treeJson;
        GetInspectorTreeJsonStr(treeJson, containerId);
        auto message = JsonUtil::Create(true);
        GetSnapshotJson(containerId, message);
        CHECK_NULL_VOID(message);
        auto sendResultTask = [treeJsonStr = std::move(treeJson), jsonSnapshotStr = message->ToString(), container]() {
            if (container->IsUseStageModel()) {
                OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
            } else {
                OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
            }
        };
        BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendResultTask));
    };
    context->GetTaskExecutor()->PostTask(
        std::move(getInspectorTask), TaskExecutor::TaskType::UI, "ArkUIGetInspectorTreeJson");
}

void LayoutInspector::CreateLayoutInfo(int32_t containerId)
{
    auto container = Container::GetFoucsed();
    return CreateContainerLayoutInfo(container);
}

void LayoutInspector::CreateLayoutInfoByWinId(uint32_t windId)
{
    auto container = Container::GetByWindowId(windId);
    if (container) {
        TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "start get container %{public}d info", container->GetInstanceId());
    }
    return CreateContainerLayoutInfo(container);
}

void LayoutInspector::GetInspectorTreeJsonStr(std::string& treeJsonStr, int32_t containerId)
{
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID(container);
#ifdef NG_BUILD
    treeJsonStr = NG::Inspector::GetInspector(true);
#else
    if (container->IsUseNewPipeline()) {
        if (containerId >= MIN_SUBCONTAINER_ID && containerId < MIN_PLUGIN_SUBCONTAINER_ID) {
            treeJsonStr = NG::Inspector::GetSubWindowInspector(true);
        } else {
            treeJsonStr = NG::Inspector::GetInspector(true);
        }
    } else {
        auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipelineContext);
        treeJsonStr = V2::Inspector::GetInspectorTree(pipelineContext, true);
    }
#endif
}

void LayoutInspector::GetSnapshotJson(int32_t containerId, std::unique_ptr<JsonValue>& message)
{
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID(container);
    OHOS::sptr<OHOS::Rosen::Window> window = GetWindow(containerId);
    CHECK_NULL_VOID(window);
    auto pixelMap = window->Snapshot();
    CHECK_NULL_VOID(pixelMap);
    auto acePixelMap = AceType::MakeRefPtr<PixelMapOhos>(pixelMap);
    CHECK_NULL_VOID(acePixelMap);
    auto imageInfo = MakeSkImageInfoFromPixelMap(acePixelMap);
    SkPixmap imagePixmap(
        imageInfo, reinterpret_cast<const void*>(acePixelMap->GetPixels()), acePixelMap->GetRowBytes());
    sk_sp<SkImage> image;
    image = SkImage::MakeFromRaster(imagePixmap, &PixelMap::ReleaseProc, PixelMap::GetReleaseContext(acePixelMap));
    CHECK_NULL_VOID(image);
    auto data = image->encodeToData(SkEncodedImageFormat::kPNG, 100);
    CHECK_NULL_VOID(data);
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    CHECK_NULL_VOID(defaultDisplay);
    auto deviceDpi = defaultDisplay->GetDpi();
    auto deviceWidth = defaultDisplay->GetWidth();
    auto deviceHeight = defaultDisplay->GetHeight();
    message->Put("type", "snapShot");
    message->Put("format", PNG_TAG);
    message->Put("width", (*pixelMap).GetWidth());
    message->Put("height", (*pixelMap).GetHeight());
    message->Put("posX", container->GetViewPosX());
    message->Put("posY", container->GetViewPosY());
    message->Put("deviceWidth", deviceWidth);
    message->Put("deviceHeight", deviceHeight);
    message->Put("deviceDpi", deviceDpi);
    int32_t encodeLength = static_cast<int32_t>(SkBase64::Encode(data->data(), data->size(), nullptr));
    message->Put("size", data->size());
    SkString info(encodeLength);
    SkBase64::Encode(data->data(), data->size(), info.writable_str());
    message->Put("pixelMapBase64", info.c_str());
}

void LayoutInspector::RegisterConnectCallback()
{
    std::call_once(loadFlag, []() {
        handlerConnectServerSo = dlopen(ARK_DEBUGGER_LIB_PATH, RTLD_NOLOAD | RTLD_NOW);
        if (handlerConnectServerSo == nullptr) {
            handlerConnectServerSo = dlopen(ARK_DEBUGGER_LIB_PATH, RTLD_NOW);
            if (handlerConnectServerSo == nullptr) {
                TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "null handlerConnectServerSo: %{public}s", dlerror());
                return;
            }
        }

        setArkUICallback = reinterpret_cast<SetArkUICallback>(dlsym(handlerConnectServerSo, "SetArkUICallback"));
        if (setArkUICallback == nullptr) {
            TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "null setArkUICallback: %{public}s", dlerror());
            return;
        }
    });

    if (setArkUICallback != nullptr) {
        setArkUICallback([](const char* message) { ProcessMessages(message); });
    }
}

void LayoutInspector::ProcessMessages(const std::string& message)
{
    uint32_t windowId = NG::Inspector::ParseWindowIdFromMsg(message);
    if (windowId == OHOS::Ace::NG::INVALID_WINDOW_ID) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "input message: %{public}s", message.c_str());
        return;
    }
    CreateLayoutInfoByWinId(windowId);
}

void LayoutInspector::HandleStopRecord()
{
    std::unique_lock<std::mutex> lock(recMutex_);
    SetRsProfilerNodeMountCallback(nullptr);
    auto jsonRoot = JsonUtil::Create(true);
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    for (auto& uiNode : recNodeInfos_) {
        if (uiNode.second != nullptr) {
            auto jsonNode = JsonUtil::Create(true);
            jsonNode->Put(RECNODE_NODEID, std::to_string(uiNode.second->GetSelfId()).c_str());
            jsonNode->Put(RECNODE_SELFID, uiNode.second->GetNodeId());
            jsonNode->Put(RECNODE_NAME, uiNode.second->GetName().c_str());
            jsonNode->Put(RECNODE_DEBUGLINE, uiNode.second->GetDebugLine().c_str());
            jsonNodeArray->PutRef(std::move(jsonNode));
        }
    }
    recNodeInfos_.clear();
    lock.unlock();
    if (jsonNodeArray->GetArraySize()) {
        jsonRoot->PutRef(RECNODE_CHILDREN, std::move(jsonNodeArray));
    }
    std::string arrayJsonStr = jsonRoot->ToString();
    auto sendResultTask = [arrayJsonStr]() {
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetRecordResults(arrayJsonStr);
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendResultTask));
}

void LayoutInspector::HandleStartRecord()
{
    // regist inner callback function
    std::unique_lock<std::mutex> lock(recMutex_);
    SetRsProfilerNodeMountCallback(LayoutInspector::HandleInnerCallback);
    lock.unlock();
    auto container = Container::GetFoucsed();
    CHECK_NULL_VOID(container);
    if (container->IsDynamicRender()) {
        container = Container::CurrentSafely();
        CHECK_NULL_VOID(container);
    }
    auto containerId = container->GetInstanceId();
    ContainerScope socpe(containerId);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto startRecordTask = []() {
        std::lock_guard<std::mutex> lock(LayoutInspector::recMutex_);
        NG::InspectorTreeMap recTreeNodes;
        NG::InspectorTreeMap offScreenTreeNodes;
        NG::Inspector::GetRecordAllPagesNodes(recTreeNodes);
        TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "Get nodes size:%{public}zu", recTreeNodes.size());
        NG::Inspector::GetOffScreenTreeNodes(offScreenTreeNodes);
        TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR, "Get offscreen nodes size:%{public}zu", offScreenTreeNodes.size());
        LayoutInspector::recNodeInfos_.swap(recTreeNodes);
        for (auto& item : offScreenTreeNodes) {
            recNodeInfos_.emplace(item);
        }
    };
    context->GetTaskExecutor()->PostTask(
        std::move(startRecordTask), TaskExecutor::TaskType::UI, "ArkUIGetInspectorTree");
}

void LayoutInspector::HandleInnerCallback(FrameNodeInfo node)
{
    // convert FrameNodeInfo --> recNode
    TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR,
        "FrameNodeInfo:selfid:%{public}" PRIu64 ",nodid:%{public}d,type:%{public}s,debugline:%{public}s",
        node.rsNodeId, node.frameNodeId, node.nodeType.c_str(), node.debugline.c_str());
    auto recNode = AceType::MakeRefPtr<NG::RecNode>();
    CHECK_NULL_VOID(recNode);
    recNode->SetSelfId(node.rsNodeId);
    recNode->SetNodeId(node.frameNodeId);
    recNode->SetName(node.nodeType);
    recNode->SetDebugLine(node.debugline);
    std::lock_guard<std::mutex> lock(recMutex_);
    recNodeInfos_.emplace(node.rsNodeId, recNode);
}
} // namespace OHOS::Ace

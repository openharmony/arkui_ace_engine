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

#include "core/components_ng/render/adapter/component_snapshot.h"

#include "transaction/rs_interfaces.h"
#include "base/log/ace_trace.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr std::chrono::duration<int, std::milli> SNAPSHOT_TIMEOUT_DURATION(3000);
constexpr std::chrono::duration<int, std::milli> CREATE_SNAPSHOT_TIMEOUT_DURATION(80);

class CustomizedCallback : public Rosen::SurfaceCaptureCallback {
public:
    CustomizedCallback(ComponentSnapshot::JsCallback&& jsCallback, WeakPtr<FrameNode> node)
        : callback_(std::move(jsCallback)), node_(std::move(node))
    {}
    ~CustomizedCallback() override = default;
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        if (callback_ == nullptr) {
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error! The callback_ is null");
            auto node = node_.Upgrade();
            CHECK_NULL_VOID(node);
            Inspector::RemoveOffscreenNode(node);
            return;
        }
        if (!pixelMap) {
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error! The pixelmap returned by the system is null");
            callback_(nullptr, ERROR_CODE_INTERNAL_ERROR, [node = node_]() {
                auto frameNode = node.Upgrade();
                CHECK_NULL_VOID(frameNode);
                Inspector::RemoveOffscreenNode(frameNode);
            });
        } else {
            TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "ComponentSnapshot successful! pixelMap.width=%{public}d pixelMap.height=%{public}d",
                pixelMap->GetWidth(), pixelMap->GetHeight());
            callback_(pixelMap, ERROR_CODE_NO_ERROR, [node = node_]() {
                auto frameNode = node.Upgrade();
                CHECK_NULL_VOID(frameNode);
                Inspector::RemoveOffscreenNode(frameNode);
            });
        }
    }

private:
    ComponentSnapshot::JsCallback callback_;
    WeakPtr<FrameNode> node_;
};

class NormalCaptureCallback : public Rosen::SurfaceCaptureCallback {
public:
    explicit NormalCaptureCallback(ComponentSnapshot::NormalCallback&& callback) : callback_(std::move(callback)) {}
    ~NormalCaptureCallback() override = default;
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        CHECK_NULL_VOID(callback_);
        callback_(pixelMap);
    }

private:
    ComponentSnapshot::NormalCallback callback_;
};

class SyncCustomizedCallback : public Rosen::SurfaceCaptureCallback {
public:
    SyncCustomizedCallback() = default;
    ~SyncCustomizedCallback() override = default;
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        if (!pixelMap) {
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "ComponentSnapshotSync Internal error! "
                "The pixelmap returned by the system is null");
            pixelMap_ = nullptr;
        } else {
            TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "ComponentSnapshotSync successful! pixelMap.width=%{public}d pixelMap.height=%{public}d",
                pixelMap->GetWidth(), pixelMap->GetHeight());
            pixelMap_ = pixelMap;
        }
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.notify_all();
    }

    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetPixelMap(std::chrono::duration<int, std::milli> timeout)
    {
        std::pair<int32_t, std::shared_ptr<Media::PixelMap>> result(ERROR_CODE_INTERNAL_ERROR, nullptr);
        std::unique_lock<std::mutex> lock(mutex_);
        auto status = cv_.wait_for(lock, timeout);
        if (status == std::cv_status::timeout) {
            return { ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT, nullptr };
        }
        if (pixelMap_) {
            result = { ERROR_CODE_NO_ERROR, pixelMap_ };
        }
        return result;
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::shared_ptr<Media::PixelMap> pixelMap_;
};
} // namespace

bool IsSnapshotRegionValid(LocalizedSnapshotRegion& snapshotRegion)
{
    if (snapshotRegion.start < 0 || snapshotRegion.end < 0 || snapshotRegion.top < 0 ||
        snapshotRegion.bottom < 0) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Snapshot reigon is invalid.");
        return false;
    }
    return true;
}

bool IsSnapshotRegionInRange(LocalizedSnapshotRegion& snapshotRegion, float& nodeWidth, float& nodeHeight)
{
    if (snapshotRegion.start > nodeWidth || snapshotRegion.end > nodeWidth || snapshotRegion.top > nodeHeight ||
        snapshotRegion.bottom > nodeHeight) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Snapshot reigon out of range.");
        return false;
    }
    return true;
}

bool SetCaptureReigon(const RefPtr<FrameNode>& node, const SnapshotOptions& options,
    Rosen::Drawing::Rect& specifiedAreaRect)
{
    RectF nodeRect = node->GetGeometryNode()->GetFrameRect();
    float nodeWidth = nodeRect.Width();
    float nodeHeight = nodeRect.Height();

    LocalizedSnapshotRegion snapshotRegion = options.snapshotRegion;
    if (!IsSnapshotRegionValid(snapshotRegion) || !IsSnapshotRegionInRange(snapshotRegion, nodeWidth, nodeHeight)) {
        return false;
    }

    auto nodeLayoutProperty = node->GetLayoutProperty();
    if (!nodeLayoutProperty) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Can't get the layout property of target node.");
        return false;
    }

    TextDirection layoutDirection = nodeLayoutProperty->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO || layoutDirection == TextDirection::INHERIT) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    bool isRegionMirror = NG::SnapshotRegionMode::LOCALIZED && layoutDirection == TextDirection::RTL;

    specifiedAreaRect = Rosen::Drawing::Rect(
        isRegionMirror ? nodeWidth - snapshotRegion.end : snapshotRegion.start,
        snapshotRegion.top,
        isRegionMirror ? nodeWidth - snapshotRegion.start : snapshotRegion.end,
        snapshotRegion.bottom);
    return true;
}

void ProcessImageNode(const RefPtr<UINode>& node, std::string& imageIds)
{
    if (node->GetTag() == V2::IMAGE_ETS_TAG) {
        auto imageNode = AceType::DynamicCast<FrameNode>(node);
        if (imageNode && AceType::DynamicCast<ImagePattern>(imageNode->GetPattern())) {
            imageIds += (std::to_string(imageNode->GetId()) + ", ");
            auto imagePattern = AceType::DynamicCast<ImagePattern>(imageNode->GetPattern());
            imagePattern->SetIsComponentSnapshotNode(true);
            imagePattern->OnVisibleAreaChange(true);
        }
    }
    auto children = node->GetChildren();
    for (const auto& child : children) {
        ProcessImageNode(child, imageIds);
    }
}

bool CheckImageSuccessfullyLoad(const RefPtr<UINode>& node, int32_t& imageCount)
{
    CHECK_NULL_RETURN(node, false);
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode && !frameNode->IsVisible()) {
        return true;
    }
    if (node->GetTag() == V2::IMAGE_ETS_TAG) {
        imageCount++;
        auto imageNode = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_RETURN(imageNode, false);
        auto imagePattern = AceType::DynamicCast<ImagePattern>(imageNode->GetPattern());
        CHECK_NULL_RETURN(imagePattern, false);
        auto imageLoadContext = imagePattern->GetImageLoadingContext().Upgrade();
        CHECK_NULL_RETURN(imageLoadContext, false);
        auto imageStateManger = imageLoadContext->GetStateManger();
        CHECK_NULL_RETURN(imageStateManger, false);

        auto result = imageStateManger->GetCurrentState() == ImageLoadingState::LOAD_SUCCESS;
        if (!result) {
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "Image loading failed! ImageId=%{public}d ImageState=%{public}d",
                imageNode->GetId(), static_cast<int32_t>(imageStateManger->GetCurrentState()));
        }
        return result;
    }

    auto children = node->GetChildren();
    for (const auto& child : children) {
        if (!CheckImageSuccessfullyLoad(child, imageCount)) {
            return false;
        }
    }
    return true;
}

bool GetTaskExecutor(const RefPtr<AceType>& customNode, RefPtr<PipelineContext>& pipeline,
    RefPtr<TaskExecutor>& executor)
{
    auto uiNode = AceType::DynamicCast<UINode>(customNode);
    if (!uiNode) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error! uiNode is nullptr, "
        "because customNode is type of %{public}s", AceType::TypeName(customNode));
        return false;
    }
    pipeline = uiNode->GetContextRefPtr();
    if (!pipeline) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error! can't get pipeline");
        return false;
    }
    executor = pipeline->GetTaskExecutor();
    if (!executor) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error! can't get executor");
        return false;
    }

    return true;
}

void HandleCreateSyncNode(const RefPtr<FrameNode>& node, const RefPtr<PipelineContext>& pipeline, std::string& imageIds)
{
    FrameNode::ProcessOffscreenNode(node);
    ProcessImageNode(node, imageIds);
    pipeline->FlushUITasks();
    pipeline->FlushModifier();
    pipeline->FlushMessages();
}

std::shared_ptr<Rosen::RSNode> ComponentSnapshot::GetRsNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(context, nullptr);
    context->AddRsNodeForCapture();
    return context->GetRSNode();
}

void TakeCaptureWithCallback(const RefPtr<FrameNode>& node, std::shared_ptr<Rosen::RSNode> rsNode,
    const SnapshotOptions& options, ComponentSnapshot::JsCallback& callback)
{
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    if (options.regionMode == NG::SnapshotRegionMode::NO_REGION) {
        rsInterface.TakeSurfaceCaptureForUI(rsNode, std::make_shared<CustomizedCallback>(std::move(callback), nullptr),
            options.scale, options.scale, options.waitUntilRenderFinished);
        return;
    }
    Rosen::Drawing::Rect specifiedAreaRect = {};
    bool isSetReigon = SetCaptureReigon(node, options, specifiedAreaRect);
    if (!isSetReigon) {
        callback(nullptr, ERROR_CODE_PARAM_INVALID, nullptr);
        return;
    }
    rsInterface.TakeSurfaceCaptureForUI(rsNode, std::make_shared<CustomizedCallback>(std::move(callback), nullptr),
        options.scale, options.scale, options.waitUntilRenderFinished, specifiedAreaRect);
}

void ComponentSnapshot::Get(const std::string& componentId, JsCallback&& callback, const SnapshotOptions& options)
{
    auto node = Inspector::GetFrameNodeByKey(componentId);
    if (!node) {
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't find a component that id or key are " SEC_PLD(%{public}s)
            ", Please check your parameters are correct",
            SEC_PARAM(componentId.c_str()));
        return;
    }

    auto rsNode = GetRsNode(node);

    if (node->GetIsLayoutNode()) {
        std::list<RefPtr<FrameNode>> children;
        node->GetOneDepthVisibleFrame(children);
        if (children.empty()) {
            callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "Children is empty from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
                SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
            return;
        }
        node = children.front();
        rsNode = GetRsNode(children.front());
    }

    if (!rsNode) {
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "RsNode is null from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
            SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
        return;
    }
    ACE_SCOPED_TRACE("ComponentSnapshot::Get_key=%s_Id=%d_RsId=%s", componentId.c_str(), node->GetId(),
        std::to_string(rsNode->GetId()).c_str());
    int32_t imageCount = 0;
    bool checkImage = CheckImageSuccessfullyLoad(node, imageCount);
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "Get ComponentSnapshot options=%{public}s Id=" SEC_PLD(%{public}d) " Depth=%{public}d Tag=%{public}s "
        "imageCount=%{public}d checkImage=%{public}d RsNodeId=%{public}" PRIu64 "",
        options.ToString().c_str(), SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str(),
        imageCount, checkImage, rsNode->GetId());
    TakeCaptureWithCallback(node, rsNode, options, callback);
}

void ComponentSnapshot::GetByUniqueId(int32_t uniqueId, JsCallback&& callback, const SnapshotOptions& options)
{
    auto node = AceType::DynamicCast<FrameNode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(uniqueId));
    if (!node) {
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't find a component that uniqueId is %{public}d, Please check your parameters are correct",
            uniqueId);
        return;
    }

    auto rsNode = GetRsNode(node);

    if (node->GetIsLayoutNode()) {
        std::list<RefPtr<FrameNode>> children;
        node->GetOneDepthVisibleFrame(children);
        if (children.empty()) {
            callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "Children is empty from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
                SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
            return;
        }
        node = children.front();
        rsNode = GetRsNode(children.front());
    }

    if (!rsNode) {
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "RsNode is null from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
            SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
        return;
    }
    ACE_SCOPED_TRACE("ComponentSnapshot::GetByUniqueId_Id=%d_RsId=%" PRIu64 "", node->GetId(), rsNode->GetId());
    int32_t imageCount = 0;
    bool checkImage = CheckImageSuccessfullyLoad(node, imageCount);
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "GetByUniqueId ComponentSnapshot options=%{public}s Id=%{public}d Tag=%{public}s imageCount=%{public}d "
        "checkImage=%{public}d RsNodeId=%{public}" PRIu64 "",
        options.ToString().c_str(), node->GetId(), node->GetTag().c_str(), imageCount, checkImage, rsNode->GetId());
    TakeCaptureWithCallback(node, rsNode, options, callback);
}

void ComponentSnapshot::Create(
    const RefPtr<AceType>& customNode, JsCallback&& callback, bool enableInspector, const SnapshotParam& param,
    bool flag)
{
    if (!customNode) {
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Internal error! customNode is nullptr");
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto stackNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, nodeId, AceType::MakeRefPtr<StackPattern>());
    RefPtr<PipelineContext> pipeline = nullptr;
    RefPtr<TaskExecutor> executor = nullptr;
    if (!GetTaskExecutor(customNode, pipeline, executor)) {
        callback(nullptr, ERROR_CODE_INTERNAL_ERROR, nullptr);
        return;
    }
    auto node = AceType::DynamicCast<FrameNode>(customNode);
    if (!node) {
        RefPtr<UINode> uiNode = AceType::DynamicCast<UINode>(customNode);
        stackNode->AddChild(uiNode);
        node = stackNode;
    }
    ACE_SCOPED_TRACE("ComponentSnapshot::Create_Tag=%s_Id=%d_Key=%s", node->GetTag().c_str(), node->GetId(),
        node->GetInspectorId().value_or("").c_str());
    FrameNode::ProcessOffscreenNode(node);
    node->SetActive();
    std::string imageIds = "";
    ProcessImageNode(node, imageIds);
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "Process off screen Node finished, root size = %{public}s Id=%{public}d Tag=%{public}s "
        "enableInspector=%{public}d imageIds=%{public}s",
        node->GetGeometryNode()->GetFrameSize().ToString().c_str(), node->GetId(), node->GetTag().c_str(),
        enableInspector, imageIds.c_str());

    if (enableInspector) {
        Inspector::AddOffscreenNode(node);
    }

    if (flag) {
        executor->PostTask(
            [node]() {
                auto pipeline = node->GetContext();
                CHECK_NULL_VOID(pipeline);
                pipeline->FlushUITasks();
                pipeline->FlushModifier();
                pipeline->FlushMessages();
            },
            TaskExecutor::TaskType::UI, "ArkUIComponentSnapshotFlushUITasks", PriorityType::VIP);
    }
    PostDelayedTaskOfBuiler(executor, std::move(callback), node, enableInspector, pipeline, param);
}

void ComponentSnapshot::GetNormalCapture(const RefPtr<FrameNode>& frameNode, NormalCallback&& callback)
{
    auto rsNode = GetRsNode(frameNode);
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    rsInterface.TakeSurfaceCaptureForUI(rsNode, std::make_shared<NormalCaptureCallback>(std::move(callback)));
}

void ComponentSnapshot::PostDelayedTaskOfBuiler(const RefPtr<TaskExecutor>& executor, JsCallback&& callback,
    const RefPtr<FrameNode>& node, bool enableInspector, const RefPtr<PipelineContext>& pipeline,
    const SnapshotParam& param)
{
    auto instanceId = pipeline->GetInstanceId();
    executor->PostDelayedTask(
        [callback, node, enableInspector, pipeline, param, instanceId]() mutable {
            ContainerScope scope(instanceId);
            BuilerTask(std::move(callback), node, enableInspector, pipeline, param);
        },
        TaskExecutor::TaskType::UI, param.delay, "ArkUIComponentSnapshotCreateCapture", PriorityType::VIP);
}

void ComponentSnapshot::BuilerTask(JsCallback&& callback, const RefPtr<FrameNode>& node, bool enableInspector,
    const RefPtr<PipelineContext>& pipeline, const SnapshotParam& param)
{
    int32_t imageCount = 0;
    if (param.checkImageStatus && !CheckImageSuccessfullyLoad(node, imageCount)) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Image loading failed! rootId=%{public}d rootNode=%{public}s",
            node->GetId(), node->GetTag().c_str());
        Inspector::RemoveOffscreenNode(node);
        callback(nullptr, ERROR_CODE_COMPONENT_SNAPSHOT_IMAGE_LOAD_ERROR, nullptr);
        return;
    }
    if (param.options.waitUntilRenderFinished) {
        pipeline->FlushUITasks();
        pipeline->FlushModifier();
        pipeline->FlushMessages();
    }
    auto rsNode = GetRsNode(node);
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "Begin to take surfaceCapture for ui, rootId=" SEC_PLD(%{public}d) " depth=%{public}d param=%{public}s "
        "imageCount=%{public}d size=%{public}s",
        SEC_PARAM(node->GetId()), node->GetDepth(), param.ToString().c_str(), imageCount,
        node->GetGeometryNode()->GetFrameSize().ToString().c_str());
    if (param.options.regionMode == NG::SnapshotRegionMode::NO_REGION) {
        rsInterface.TakeSurfaceCaptureForUI(
            rsNode,
            std::make_shared<CustomizedCallback>(std::move(callback), enableInspector ? node : nullptr),
            param.options.scale, param.options.scale, param.options.waitUntilRenderFinished);
        return;
    }
    Rosen::Drawing::Rect specifiedAreaRect = {};
    bool isSetReigon = SetCaptureReigon(node, param.options, specifiedAreaRect);
    if (!isSetReigon) {
        callback(nullptr, ERROR_CODE_PARAM_INVALID, nullptr);
        return;
    }
    rsInterface.TakeSurfaceCaptureForUI(
        rsNode,
        std::make_shared<CustomizedCallback>(std::move(callback), enableInspector ? node : nullptr),
        param.options.scale, param.options.scale, param.options.waitUntilRenderFinished, specifiedAreaRect);
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> ComponentSnapshot::GetSync(
    RefPtr<FrameNode>& node, const SnapshotOptions& options)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("ComponentSnapshot::GetSyncStart_%s", node->GetInspectorIdValue("").c_str());
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> result(ERROR_CODE_INTERNAL_ERROR, nullptr);
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> regionResult(ERROR_CODE_PARAM_INVALID, nullptr);
    CHECK_NULL_RETURN(node, result);
    auto rsNode = GetRsNode(node);

    if (node->GetIsLayoutNode()) {
        std::list<RefPtr<FrameNode>> children;
        node->GetOneDepthVisibleFrame(children);
        if (children.empty()) {
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "Children is empty from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
                SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
            return result;
        }
        node = children.front();
        rsNode = GetRsNode(children.front());
    }

    if (!rsNode) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "RsNode is null from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
            SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
        return result;
    }
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "GetSync ComponentSnapshot options=%{public}s Id=" SEC_PLD(%{public}d) " Depth=%{public}d Tag=%{public}s "
        "RsNodeId=%{public}" PRIu64 "",
        options.ToString().c_str(), SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str(),
        rsNode->GetId());
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    auto syncCallback = std::make_shared<SyncCustomizedCallback>();
    {
        ACE_SCOPED_TRACE("ComponentSnapshot::GetSync_TakeSurfaceCaptureForUI_%s_%d_%" PRIu64 "",
            node->GetInspectorIdValue("").c_str(), node->GetId(), rsNode->GetId());
    }
    if (options.regionMode == NG::SnapshotRegionMode::NO_REGION) {
        rsInterface.TakeSurfaceCaptureForUI(rsNode, syncCallback,
            options.scale, options.scale, options.waitUntilRenderFinished);
        return syncCallback->GetPixelMap(SNAPSHOT_TIMEOUT_DURATION);
    }
    Rosen::Drawing::Rect specifiedAreaRect = {};
    bool isSetReigon = SetCaptureReigon(node, options, specifiedAreaRect);
    if (!isSetReigon) {
        return regionResult;
    }
    rsInterface.TakeSurfaceCaptureForUI(rsNode, syncCallback,
        options.scale, options.scale, options.waitUntilRenderFinished, specifiedAreaRect);
    return syncCallback->GetPixelMap(SNAPSHOT_TIMEOUT_DURATION);
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> ComponentSnapshot::GetSync(const std::string& componentId,
    const SnapshotOptions& options)
{
    CHECK_RUN_ON(UI);
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> result(ERROR_CODE_INTERNAL_ERROR, nullptr);
    auto node = Inspector::GetFrameNodeByKey(componentId);
    if (!node) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't find a component that id or key are " SEC_PLD(%{public}s)
            ", Please check your parameters are correct",
            SEC_PARAM(componentId.c_str()));
        return result;
    }

    return GetSync(node, options);
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> TakeCaptureWhenGetSync(const RefPtr<FrameNode>& node,
    std::shared_ptr<Rosen::RSNode> rsNode, const SnapshotOptions& options)
{
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> regionResult(ERROR_CODE_PARAM_INVALID, nullptr);
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    auto syncCallback = std::make_shared<SyncCustomizedCallback>();
    {
        ACE_SCOPED_TRACE("ComponentSnapshot::GetSyncByUniqueId_TakeSurfaceCaptureForUI_%d_%" PRIu64 "",
            node->GetId(), rsNode->GetId());
    }
    if (options.regionMode == NG::SnapshotRegionMode::NO_REGION) {
        rsInterface.TakeSurfaceCaptureForUI(rsNode, syncCallback,
            options.scale, options.scale, options.waitUntilRenderFinished);
        return syncCallback->GetPixelMap(SNAPSHOT_TIMEOUT_DURATION);
    }
    Rosen::Drawing::Rect specifiedAreaRect = {};
    bool isSetReigon = SetCaptureReigon(node, options, specifiedAreaRect);
    if (!isSetReigon) {
        return regionResult;
    }
    rsInterface.TakeSurfaceCaptureForUI(rsNode, syncCallback,
        options.scale, options.scale, options.waitUntilRenderFinished, specifiedAreaRect);
    return syncCallback->GetPixelMap(SNAPSHOT_TIMEOUT_DURATION);
}

std::pair<int32_t, std::shared_ptr<Media::PixelMap>> ComponentSnapshot::GetSyncByUniqueId(int32_t uniqueId,
    const SnapshotOptions& options)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("ComponentSnapshot::GetSyncByUniqueId_%d", uniqueId);
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> result(ERROR_CODE_INTERNAL_ERROR, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(uniqueId));
    if (!node) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't find a component that uniqueId is %{public}d, Please check your parameters are correct", uniqueId);
        return result;
    }

    auto rsNode = GetRsNode(node);

    if (node->GetIsLayoutNode()) {
        std::list<RefPtr<FrameNode>> children;
        node->GetOneDepthVisibleFrame(children);
        if (children.empty()) {
            TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                "Children is empty from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
                SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
            return result;
        }
        node = children.front();
        rsNode = GetRsNode(children.front());
    }

    if (!rsNode) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "RsNode is null from FrameNode(Id=" SEC_PLD(%{public}d) ",Depth=%{public}d,Tag=%{public}s)",
            SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
        return result;
    }
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "GetSyncByUniqueId ComponentSnapshot options=%{public}s Id=" SEC_PLD(%{public}d)
        " Depth=%{public}d Tag=%{public}s RsNodeId=%{public}" PRIu64 "",
        options.ToString().c_str(), SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str(),
        rsNode->GetId());
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> captureResult = TakeCaptureWhenGetSync(node, rsNode, options);
    return captureResult;
}

// Note: do not use this method, it's only called in drag procedure process.
std::shared_ptr<Media::PixelMap> ComponentSnapshot::CreateSync(
    const RefPtr<AceType>& customNode, const SnapshotParam& param)
{
    if (!customNode) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "CreateSync Internal error! customNode is nullptr");
        return nullptr;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto stackNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, nodeId, AceType::MakeRefPtr<StackPattern>());
    RefPtr<PipelineContext> pipeline = nullptr;
    RefPtr<TaskExecutor> executor = nullptr;
    if (!GetTaskExecutor(customNode, pipeline, executor)) {
        return nullptr;
    }
    auto node = AceType::DynamicCast<FrameNode>(customNode);
    if (!node) {
        RefPtr<UINode> uiNode = AceType::DynamicCast<UINode>(customNode);
        stackNode->AddChild(uiNode);
        node = stackNode;
    }
    ACE_SCOPED_TRACE("ComponentSnapshot::CreateSync_Tag=%s_Id=%d_Key=%s", node->GetTag().c_str(), node->GetId(),
        node->GetInspectorId().value_or("").c_str());
    std::string imageIds = "";
    HandleCreateSyncNode(node, pipeline, imageIds);
    int32_t imageCount = 0;
    bool checkImage = CheckImageSuccessfullyLoad(node, imageCount);
    if (!checkImage) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Image loading failed! rootId=" SEC_PLD(%{public}d) " depth=%{public}d rootNode=%{public}s",
            SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
        return nullptr;
    }
    auto rsNode = GetRsNode(node);
    if (!rsNode) {
        TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
            "Can't get RsNode! rootId=" SEC_PLD(%{public}d) " depth=%{public}d rootNode=%{public}s",
            SEC_PARAM(node->GetId()), node->GetDepth(), node->GetTag().c_str());
        return nullptr;
    }
    auto& rsInterface = Rosen::RSInterfaces::GetInstance();
    auto syncCallback = std::make_shared<SyncCustomizedCallback>();
    rsInterface.TakeSurfaceCaptureForUI(rsNode, syncCallback, 1.f, 1.f, true);
    auto pair = syncCallback->GetPixelMap(CREATE_SNAPSHOT_TIMEOUT_DURATION);
    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
        "CreateSync, root size=%{public}s Id=" SEC_PLD(%{public}d) " depth=%{public}d Tag=%{public}s code:%{public}d "
        "imageIds=%{public}s",
        node->GetGeometryNode()->GetFrameSize().ToString().c_str(), SEC_PARAM(node->GetId()), node->GetDepth(),
        node->GetTag().c_str(), pair.first, imageIds.c_str());
    return pair.second;
}
} // namespace OHOS::Ace::NG

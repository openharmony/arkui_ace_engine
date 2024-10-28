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
#include "window_scene_layout_manager.h"

#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/panel_scene.h"
#include "core/components_ng/pattern/window_scene/scene/input_scene.h"
#include "core/components_ng/pattern/window_scene/screen/screen_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "parameters.h"
#include "session/host/include/session.h"
#include "session_manager/include/scene_session_manager.h"

namespace {
constexpr uint64_t SCREEN_ID_INVALID = -1ULL;
constexpr float EPSILON = 1e-3;
}
namespace OHOS::Ace::NG {
WindowSceneLayoutManager* WindowSceneLayoutManager::GetInstance()
{
    auto container = Container::Current();
    if (!container || !container->IsScenceBoardWindow() || !Rosen::Session::IsScbCoreEnabled()) {
        return nullptr;
    }
    static WindowSceneLayoutManager* instance = nullptr;
    if (instance == nullptr) {
        instance = new WindowSceneLayoutManager();
        instance->Init();
    }
    return instance;
}

void WindowSceneLayoutManager::Init()
{
    Rosen::SceneSessionManager::GetInstance().SetDumpUITreeFunc(
        [this](uint64_t screenId, std::string& info) {
            isCoreDebugEnable_ = system::GetParameter("debug.window.coredebug.enabled", "0") == "1";
            GetTotalUITreeInfo(screenId, info);
        }
    );
}

bool WindowSceneLayoutManager::IsNodeDirty(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(context, false);
    auto rsNode = context->GetRSNode();
    CHECK_NULL_RETURN(rsNode, false);
    return rsNode->IsAppearanceDirty() || rsNode->IsGeometryDirty();
}

bool WindowSceneLayoutManager::IsNodeVisible(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(context, false);
    auto rsNode = context->GetRSNode();
    CHECK_NULL_RETURN(rsNode, false);
    bool isVisible = node->IsVisible();
    float opacityVal = context->GetOpacityValue(1.0f);
    bool opaque = (opacityVal - 0.0f) > std::numeric_limits<float>::epsilon();
    bool ret = isVisible && opaque;
    if (isCoreDebugEnable_) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "winId:%{public}d name:%{public}s frameNodeId:%{public}d "
            "isVisible:%{public}d opaque:%{public}f ret:%{public}u", GetWindowId(node),
            GetWindowName(node).c_str(), node->GetId(), isVisible, opacityVal, ret);
    }
    return ret;
}

int32_t WindowSceneLayoutManager::GetNodeZIndex(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, ZINDEX_DEFAULT_VALUE);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(context, ZINDEX_DEFAULT_VALUE);
    return context->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
}

uint64_t WindowSceneLayoutManager::GetScreenId(const RefPtr<FrameNode>& screenNode)
{
    CHECK_NULL_RETURN(screenNode, SCREEN_ID_INVALID);
    auto pattern = screenNode->GetPattern<ScreenPattern>();
    CHECK_NULL_RETURN(pattern, SCREEN_ID_INVALID);
    auto screenSession = pattern->GetScreenSession();
    CHECK_NULL_RETURN(screenSession, SCREEN_ID_INVALID);
    return screenSession->GetScreenId();
}

void WindowSceneLayoutManager::UpdateGeometry(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& parentNode,
    bool isParentTransformScene)
{
    CHECK_NULL_VOID(node);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto rsNode = context->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    auto globalGeometry = isParentTransformScene ? std::make_shared<Rosen::RSObjAbsGeometry>()
        : GetGlobalGeometry(parentNode);
    if (!globalGeometry) {
        if (!WindowSceneHelper::IsScreenScene(node->GetWindowPatternType())) {
            TAG_LOGW(AceLogTag::ACE_WINDOW_PIPELINE, "windowName:%{public}s, global geo is null and new",
                GetWindowName(node).c_str());
        }
        globalGeometry = std::make_shared<Rosen::RSObjAbsGeometry>();
    }
    rsNode->UpdateLocalGeometry();
    if (WindowSceneHelper::IsTransformScene(node->GetWindowPatternType())) {
        // once current transform scene, set pos/trans 0, to make global position relative to transform scene
        if (auto localGeo = rsNode->GetLocalGeometry()) {
            localGeo->SetPosition(0.0f, 0.0f);
            localGeo->SetTranslateX(0.0f);
            localGeo->SetTranslateY(0.0f);
        } else {
            TAG_LOGW(AceLogTag::ACE_WINDOW_PIPELINE, "windowName:%{public}s, local geo is null",
                GetWindowName(node).c_str());
        }
    }
    rsNode->UpdateGlobalGeometry(globalGeometry);
    rsNode->MarkDirty(Rosen::NodeDirtyType::GEOMETRY, false);
    rsNode->MarkDirty(Rosen::NodeDirtyType::APPEARANCE, false);
    DumpNodeInfo(node, parentNode, "UpdateGeometry");
}

std::shared_ptr<Rosen::RSNode> WindowSceneLayoutManager::GetRSNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(context, nullptr);
    return context->GetRSNode();
}

std::shared_ptr<Rosen::RSObjAbsGeometry> WindowSceneLayoutManager::GetGlobalGeometry(const RefPtr<FrameNode>& node)
{
    auto rsNode = GetRSNode(node);
    CHECK_NULL_RETURN(rsNode, nullptr);
    return rsNode->GetGlobalGeometry();
}

std::shared_ptr<Rosen::RSObjAbsGeometry> WindowSceneLayoutManager::GetLocalGeometry(const RefPtr<FrameNode>& node)
{
    auto rsNode = GetRSNode(node);
    CHECK_NULL_RETURN(rsNode, nullptr);
    return rsNode->GetLocalGeometry();
}

void WindowSceneLayoutManager::FillWindowSceneInfo(const RefPtr<FrameNode>& node,
    TraverseResult& res, bool isAncestorRecent, bool notSyncPosition)
{
    auto rsNode = GetRSNode(node);
    if (!rsNode) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "name:%{public}s rsNode is null", GetWindowName(node).c_str());
        return;
    }
    auto globalGeometry = isAncestorRecent ? std::make_shared<Rosen::RSObjAbsGeometry>()
                                           : rsNode->GetGlobalGeometry();
    auto localGeometry = rsNode->GetLocalGeometry();
    if (isAncestorRecent && !localGeometry) {
        localGeometry = std::make_shared<Rosen::RSObjAbsGeometry>();
    }
    if (!globalGeometry || !localGeometry) {
        if (isCoreDebugEnable_) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "name:%{public}s globalGeo is null:%{public}d localGeo:%{public}d",
                GetWindowName(node).c_str(), globalGeometry == nullptr, localGeometry == nullptr);
        }
        return;
    }
    Rosen::SessionUIParam uiParam;
    auto width = localGeometry->GetWidth();
    auto height = localGeometry->GetHeight();
    if (std::abs(width - 0.0f) < EPSILON || std::abs(height - 0.0f) < EPSILON) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "name:%{public}s w:%{public}f h:%{public}f is 0",
            GetWindowName(node).c_str(), width, height);
        return;
    }
    if (isAncestorRecent) {
        uiParam.rect_ = { localGeometry->GetX(), localGeometry->GetY(), width, height };
    } else {
        auto absRect = globalGeometry->GetAbsRect();
        uiParam.rect_ = { absRect.GetLeft(), absRect.GetTop(), width, height };
        uiParam.scaleX_ = absRect.GetWidth() / width;
        uiParam.scaleY_ = absRect.GetHeight() / height;
    }
    uiParam.needSync_ = notSyncPosition ? false : true;
    auto matrix = globalGeometry->GetAbsMatrix();
    uiParam.transX_ = std::round(matrix.Get(Rosen::Drawing::Matrix::TRANS_X) - rsNode->GetGlobalPositionX());
    uiParam.transY_ = std::round(matrix.Get(Rosen::Drawing::Matrix::TRANS_Y) - rsNode->GetGlobalPositionY());
    uiParam.pivotX_ = globalGeometry->GetPivotX();
    uiParam.pivotY_ = globalGeometry->GetPivotY();
    uiParam.zOrder_ = static_cast<uint32_t>(res.zOrderCnt_);
    auto windowId = GetWindowId(node);
    uiParam.sessionName_ = GetWindowName(node);
    if (isAncestorRecent) {
        // panel scene self should be interactive, others should be false
        // default interactive is true
        uiParam.interactive_ = WindowSceneHelper::IsPanelScene(node->GetWindowPatternType());
    }
    res.uiParams_[windowId] = std::move(uiParam);
}

// once return false: need sync position; else not sync
bool WindowSceneLayoutManager::NoNeedSyncScenePanelGlobalPosition(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    if (!WindowSceneHelper::IsPanelScene(node->GetWindowPatternType())) {
        return false;
    }
    auto windowPattern = node->GetPattern<PanelScene>();
    if (windowPattern == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "recent SystemWindowScene is null. node:%{public}s",
            GetWindowName(node).c_str());
        return false;
    }
    auto session = windowPattern->GetSession();
    if (session == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "recent session is null. node:%{public}s",
            GetWindowName(node).c_str());
        return false;
    }
    return !session->IsNeedSyncScenePanelGlobalPosition();
}

void WindowSceneLayoutManager::FlushWindowPatternInfo(const RefPtr<FrameNode>& screenNode)
{
    if (isCoreDebugEnable_) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "------------------- Begin FlushWindowPatternInfo ------------------");
    }
    auto screenId = GetScreenId(screenNode);
    if (screenId == SCREEN_ID_INVALID) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE,
            "tag:%{public}s screenId:%{public}" PRIu64, screenNode->GetTag().c_str(), screenId);
        return;
    }
    TraverseResult res;
    res.zOrderCnt_ = 0;
    res.screenId_ = screenId;
    UpdateGeometry(screenNode, nullptr, false);
    TraverseTree(screenNode, res, false, IsNodeDirty(screenNode), false);
    if (isCoreDebugEnable_) {
        DumpFlushInfo(screenId, res);
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "------------------- End FlushWindowPatternInfo ------------------");
    }
    // cannot post ui task, since flush may not excute on next frame
    Rosen::SceneSessionManager::GetInstance().FlushUIParams(screenId, std::move(res.uiParams_));
}

bool WindowSceneLayoutManager::IsRecentContainerState(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    if (!WindowSceneHelper::IsPanelScene(node->GetWindowPatternType())) {
        return false;
    }
    auto windowPattern = node->GetPattern<PanelScene>();
    if (windowPattern == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "recent SystemWindowScene is null. node:%{public}s",
            GetWindowName(node).c_str());
        return false;
    }
    auto session = windowPattern->GetSession();
    if (session == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "recent session is null. node:%{public}s",
            GetWindowName(node).c_str());
        return false;
    }
    return session->GetSystemTouchable();
}

void WindowSceneLayoutManager::TraverseTree(const RefPtr<FrameNode>& rootNode, TraverseResult& res,
    bool isAncestorRecent, bool isAncestorDirty, bool notSyncPosition)
{
    CHECK_NULL_VOID(rootNode);
    auto parentType = rootNode->GetWindowPatternType();
    for (auto& weakNode : rootNode->GetFrameChildren()) {
        auto node = weakNode.Upgrade();
        // when current layer is invisible, no need traverse next
        if (!node || !IsNodeVisible(node)) {
            continue;
        }
        // once delete in recent, need update Zorder
        uint32_t currentZorder = res.zOrderCnt_;
        if (WindowSceneHelper::IsWindowPattern(node)) {
            currentZorder = std::max(res.zOrderCnt_, static_cast<uint32_t>(GetNodeZIndex(node)));
        }
        // only window pattern need cal zorder
        bool hasWindowSession = WindowSceneHelper::HasWindowSession(node);
        if (hasWindowSession) {
            res.zOrderCnt_ = currentZorder++; // keep last zorder as current zorder
        }
        notSyncPosition = (notSyncPosition || NoNeedSyncScenePanelGlobalPosition(node));

        // process recent and child node
        if (isAncestorRecent || IsRecentContainerState(node)) {
            isAncestorRecent = true;
        } else {
            if (isAncestorDirty || IsNodeDirty(node)) {
                isAncestorDirty = true;
                UpdateGeometry(node, rootNode, WindowSceneHelper::IsTransformScene(parentType));
            }
        }
        // only window pattern but not transform scene need sync info
        if (hasWindowSession) {
            FillWindowSceneInfo(node, res, isAncestorRecent, notSyncPosition);
            DumpNodeInfo(node, rootNode, "AfterFillWindowSceneInfo");
        }

        res.zOrderCnt_ = currentZorder; // use cnt++ for next zorder cnt
        auto type = node->GetWindowPatternType();
        if (!WindowSceneHelper::IsSystemWindowScene(type) && WindowSceneHelper::IsSystemWindowScene(parentType)) {
            TAG_LOGD(AceLogTag::ACE_WINDOW_PIPELINE, "name:%{public}s child of systemScene continue",
                GetWindowName(node).c_str());
            continue; // calculate last system window scene next layer
        }
        if (isCoreDebugEnable_) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "finish TraverseTree winId:%{public}d name:%{public}s"
                "nodeName:%{public}s tag:%{public}s zorder:%{public}u isAncestorRecent:%{public}d "
                "isAncestorDirty:%{public}d hasWindowSession:%{public}d, notSyncPosition:%{public}d",
                GetWindowId(node), GetWindowName(node).c_str(),
                node->GetInspectorId()->c_str(), node->GetTag().c_str(), res.zOrderCnt_,
                isAncestorRecent, isAncestorDirty, hasWindowSession, notSyncPosition);
        }
        TraverseTree(node, res, isAncestorRecent, isAncestorDirty, notSyncPosition);
    }
}

// dump funcs
template<typename T>
uint32_t WindowSceneLayoutManager::GetWindowIdInner(const RefPtr<T>& windowPattern)
{
    if (windowPattern == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "windowPattern is null");
        return 0;
    }
    auto session = windowPattern->GetSession();
    if (session == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "window session is null");
        return 0;
    }
    return session->GetWindowId();
}

uint32_t WindowSceneLayoutManager::GetWindowId(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, 0);

    auto type = static_cast<WindowPatternType>(node->GetWindowPatternType());
    switch (type) {
        case WindowPatternType::DEFAULT: // fallthrough
        case WindowPatternType::TRANSFORM_SCENE:
            return 0; // invalid window Id
        case WindowPatternType::PANEL_SCENE:
            return GetWindowIdInner(node->GetPattern<PanelScene>());
        case WindowPatternType::INPUT_SCENE:
            return GetWindowIdInner(node->GetPattern<InputScene>());
        case WindowPatternType::SYSTEM_WINDOW_SCENE: {
            auto windowPattern = node->GetPattern<SystemWindowScene>();
            if (windowPattern == nullptr || windowPattern->GetSession() == nullptr) {
                TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "SystemWindowScene or session is null. type:%{public}u", type);
                return 0;
            }
            return GetWindowIdInner(node->GetPattern<SystemWindowScene>());
        }
        case WindowPatternType::WINDOW_SCENE: {
            return GetWindowIdInner(node->GetPattern<WindowScene>());
        }
        default:
            break;
    }
    return 0;
}

template<typename T>
std::string WindowSceneLayoutManager::GetWindowNameInner(const RefPtr<T>& windowPattern)
{
    if (windowPattern == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "windowPattern is null");
        return {};
    }
    auto session = windowPattern->GetSession();
    if (session == nullptr) {
        TAG_LOGE(AceLogTag::ACE_WINDOW_PIPELINE, "window session is null");
        return {};
    }
    return session->GetWindowName();
}

std::string WindowSceneLayoutManager::GetWindowName(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    std::string name;
    auto type = static_cast<WindowPatternType>(node->GetWindowPatternType());
    switch (type) {
        case WindowPatternType::DEFAULT:
        case WindowPatternType::TRANSFORM_SCENE:
            break;
        case WindowPatternType::PANEL_SCENE: {
            name = GetWindowNameInner(node->GetPattern<PanelScene>());
            break;
        }
        case WindowPatternType::INPUT_SCENE: {
            name = GetWindowNameInner(node->GetPattern<InputScene>());
            break;
        }
        case WindowPatternType::SYSTEM_WINDOW_SCENE: {
            name = GetWindowNameInner(node->GetPattern<SystemWindowScene>());
            break;
        }
        case WindowPatternType::WINDOW_SCENE: {
            name = GetWindowNameInner(node->GetPattern<WindowScene>());
            break;
        }
        default:
            break;
    }
    return name + "_" + node->GetInspectorIdValue("") + "_" + node->GetTag();
}


void WindowSceneLayoutManager::DumpFlushInfo(uint64_t screenId, TraverseResult& res)
{
    if (!isCoreDebugEnable_) {
        return;
    }
    for (auto& [winId, uiParam] : res.uiParams_) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "DumpFlushInfo screenId:%{public}" PRIu64 " windowId:%{public}d"
            " name:%{public}s rect:%{public}s, scaleX:%{public}f, scaleY:%{public}f, transX:%{public}f"
            " transY:%{public}f pivotX:%{public}f, pivotY:%{public}f zOrder:%{public}u, interactive:%{public}d",
            screenId, winId, uiParam.sessionName_.c_str(), uiParam.rect_.ToString().c_str(), uiParam.scaleX_,
            uiParam.scaleY_, uiParam.transX_, uiParam.transY_,
            uiParam.pivotX_, uiParam.pivotY_, uiParam.zOrder_, uiParam.interactive_);
    }
}

uint64_t WindowSceneLayoutManager::GetRSNodeId(const RefPtr<FrameNode>& node)
{
    auto rsNode = GetRSNode(node);
    CHECK_NULL_RETURN(rsNode, 0);
    return rsNode->GetId();
}

void WindowSceneLayoutManager::DumpNodeInfo(const RefPtr<FrameNode>& node,
    const RefPtr<FrameNode>& parentNode, const std::string& reason)
{
    if (!isCoreDebugEnable_) {
        return;
    }
    CHECK_NULL_VOID(node);
    int32_t parentId = parentNode ? parentNode->GetId() : 0;
    auto rsNode = GetRSNode(node);
    CHECK_NULL_VOID(rsNode);
    auto nodeGeometry = rsNode->GetGlobalGeometry();
    if (!nodeGeometry) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_PIPELINE,
            "reason:%{public}s globalGeometry name:%{public}s lrsId:%{public}" PRIu64 " %{public}d"
            "parentRSId:%{public}" PRIu64 " frameNodeId:%{public}d global geFnoMetry is null",
            reason.c_str(), GetWindowName(node).c_str(), GetRSNodeId(node), node->GetId(),
            GetRSNodeId(parentNode), parentId);
        return;
    }
    auto nodeLocalGeometry = rsNode->GetLocalGeometry();
    if (!nodeLocalGeometry) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_PIPELINE,
            "reason:%{public}s localGeometry name:%{public}s lrsId:%{public}" PRIu64 " parentRSId:%{public}" PRIu64
            " localGeo is null", reason.c_str(), GetWindowName(node).c_str(),
            GetRSNodeId(node), GetRSNodeId(parentNode));
        return;
    }

    Rosen::WSRect tempGlobal = { nodeGeometry->GetX(), nodeGeometry->GetY(),
        nodeGeometry->GetWidth(), nodeGeometry->GetHeight() };
    Rosen::WSRect tempLocal = { nodeLocalGeometry->GetX(), nodeLocalGeometry->GetY(),
        nodeLocalGeometry->GetWidth(), nodeLocalGeometry->GetHeight() };
    auto localMatrix = nodeLocalGeometry->GetAbsMatrix();
    auto globalMatrix = nodeGeometry->GetAbsMatrix();
    float localTransX = localMatrix.Get(Rosen::Drawing::Matrix::TRANS_X);
    float localTransY = localMatrix.Get(Rosen::Drawing::Matrix::TRANS_Y);
    float globalTransX = globalMatrix.Get(Rosen::Drawing::Matrix::TRANS_X);
    float globalTransY = globalMatrix.Get(Rosen::Drawing::Matrix::TRANS_Y);
    auto absGlobalRect = nodeGeometry->GetAbsRect();
    auto absLocalRect = nodeLocalGeometry->GetAbsRect();
    auto localScaleX = localMatrix.Get(Rosen::Drawing::Matrix::SCALE_X);
    auto localScaleY = localMatrix.Get(Rosen::Drawing::Matrix::SCALE_Y);
    auto gScaleX = globalMatrix.Get(Rosen::Drawing::Matrix::SCALE_X);
    auto gScaleY = globalMatrix.Get(Rosen::Drawing::Matrix::SCALE_Y);
    float globalPosX = rsNode->GetGlobalPositionX();
    float globalPosY = rsNode->GetGlobalPositionY();
    TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE,
        "DumpNodeInfo reason:%{public}s name:%{public}s lrsId:%{public}" PRIu64 " parentRSId:%{public}" PRIu64 ""
        " frameNodeId:%{public}d [Rect:%{public}s lTransX:%{public}f lTransY:%{public}f absLocalRect:%{public}s, "
        "gRect:%{public}s gTransX:%{public}f gTransY:%{public}f globalPosX:%{public}f, globalPosY:%{public}f, "
        "absGlobalRect:%{public}s lScaleX:%{public}f lScaleY:%{public}f gScaleX:%{public}f gScaleY:%{public}f]",
        GetWindowName(node).c_str(), reason.c_str(), GetRSNodeId(node), GetRSNodeId(parentNode), parentId,
        tempLocal.ToString().c_str(), localTransX, localTransY,
        absLocalRect.ToString().c_str(), tempGlobal.ToString().c_str(), globalTransX, globalTransY, globalPosX,
        globalPosY, absGlobalRect.ToString().c_str(), localScaleX, localScaleY, gScaleX, gScaleY);
}

void WindowSceneLayoutManager::RegisterScreenNode(uint64_t screenId, const RefPtr<FrameNode>& node)
{
    screenNodeMap_[screenId] = node;
    TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "screenNode:%{public}" PRIu64 " register, size:%{public}d",
        screenId, static_cast<uint32_t>(screenNodeMap_.size()));
}

void WindowSceneLayoutManager::UnregisterScreenNode(uint64_t screenId)
{
    screenNodeMap_.erase(screenId);
    TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "screenNode:%{public}" PRIu64 " unregister, size:%{public}d",
        screenId, static_cast<uint32_t>(screenNodeMap_.size()));
}

void WindowSceneLayoutManager::GetUINodeInfo(const RefPtr<FrameNode>& node,
    int32_t parentId, std::ostringstream& oss)
{
    CHECK_NULL_VOID(node);
    auto context = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto rsNode = context->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    oss << " name: " << GetWindowName(node);
    oss << " isVisible: " << node->IsVisible();
    oss << " opacity: " << context->GetOpacityValue(1.0f);
    oss << " patternType: " << node->GetWindowPatternType();
    auto globalGeometry = GetGlobalGeometry(node);
    auto localGeometry = GetLocalGeometry(node);
    if (globalGeometry && localGeometry) {
        auto absRect = globalGeometry->GetAbsRect();
        oss << " resRect: [" << absRect.GetLeft() << ", " << absRect.GetTop() << ", "
            << localGeometry->GetWidth() << ", " << localGeometry->GetHeight() << "]";
        auto matrix = globalGeometry->GetAbsMatrix();
        oss << " globalScale: [ " << matrix.Get(Rosen::Drawing::Matrix::SCALE_X) << ", "
            << matrix.Get(Rosen::Drawing::Matrix::SCALE_Y) << "],";
        oss << " globalPos: [" << rsNode->GetGlobalPositionX() << ", " << rsNode->GetGlobalPositionY() << "],";
        oss << " pivot: [" << globalGeometry->GetPivotX() << ", " << globalGeometry->GetPivotY() << "],";
    } else {
        oss << " globalGeometry: [null],";
    }
    if (localGeometry) {
        auto absRect = localGeometry->GetAbsRect();
        oss << " localRect: [" << absRect.GetLeft() << ", " << absRect.GetTop() << ", "
            << localGeometry->GetWidth() << ", " << localGeometry->GetHeight() << "]";
        auto matrix = localGeometry->GetAbsMatrix();
        oss << " localScale: [" << matrix.Get(Rosen::Drawing::Matrix::SCALE_X) << ", "
            << matrix.Get(Rosen::Drawing::Matrix::SCALE_Y) << "],";
        oss << " localTrans: [" << matrix.Get(Rosen::Drawing::Matrix::TRANS_X) << ", "
            << matrix.Get(Rosen::Drawing::Matrix::TRANS_Y) << "],";
        oss << " localPos: [" << localGeometry->GetX() << ", "
            << localGeometry->GetY() << "],";
    } else {
        oss << " localGeometry: [null],";
    }
    oss << " requestZIndex: " << context->GetZIndexValue(ZINDEX_DEFAULT_VALUE);
    oss << " rsId: " << GetRSNodeId(node);
    oss << " frameNodeId: " << node->GetId();
    oss << " parentFrameNodeId: " << parentId << std::endl;
}

void WindowSceneLayoutManager::GetTotalUITreeInfo(uint64_t screenId, std::string& info)
{
    TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "begin:%{public}" PRIu64, screenId);
    if (!mainHandler_) {
        auto runner = AppExecFwk::EventRunner::GetMainEventRunner();
        mainHandler_ = std::make_shared<AppExecFwk::EventHandler>(runner);
    }
    auto task = [this, screenId, &info] {
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "begin task GetTotalUITreeInfo:%{public}" PRIu64, screenId);
        if (screenNodeMap_.count(screenId) == 0) {
            TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "screenNode:%{public}" PRIu64 " not exists", screenId);
            return;
        }
        std::ostringstream oss;
        GetUITreeInfo(screenNodeMap_[screenId], 0, 0, oss);
        oss << "-------------------------------------RSTree-----------------------------------" << std::endl;
        GetRSNodeTreeInfo(GetRSNode(screenNodeMap_[screenId]), 0, oss);
        info.append(oss.str());
    };
    mainHandler_->PostSyncTask(std::move(task), "GetTotalUITreeInfo", AppExecFwk::EventQueue::Priority::IMMEDIATE);
}

void WindowSceneLayoutManager::GetUITreeInfo(const RefPtr<FrameNode>& node, int32_t depth,
    int32_t parentId, std::ostringstream& oss)
{
    if (!node) {
        return;
    }
    for (int32_t i = 0; i < depth; ++i) {
        oss << "  ";
    }
    oss << "| ";
    GetUINodeInfo(node, parentId, oss);
    for (auto& weakNode : node->GetFrameChildren()) {
        auto child = weakNode.Upgrade();
        if (!child) {
            continue;
        }
        GetUITreeInfo(child, depth + 1, node->GetId(), oss);
    }
}

void WindowSceneLayoutManager::DumpRSNodeType(Rosen::RSUINodeType nodeType, std::ostringstream& oss)
{
    switch (nodeType) {
        case Rosen::RSUINodeType::DISPLAY_NODE: {
            oss << "DISPLAY_NODE";
            break;
        }
        case Rosen::RSUINodeType::RS_NODE: {
            oss << "RS_NODE";
            break;
        }
        case Rosen::RSUINodeType::SURFACE_NODE: {
            oss << "SURFACE_NODE";
            break;
        }
        case Rosen::RSUINodeType::CANVAS_NODE: {
            oss << "CANVAS_NODE";
            break;
        }
        case Rosen::RSUINodeType::ROOT_NODE: {
            oss << "ROOT_NODE";
            break;
        }
        case Rosen::RSUINodeType::PROXY_NODE: {
            oss << "PROXY_NODE";
            break;
        }
        case Rosen::RSUINodeType::CANVAS_DRAWING_NODE: {
            oss << "CANVAS_DRAWING_NODE";
            break;
        }
        case Rosen::RSUINodeType::EFFECT_NODE: {
            oss << "EFFECT_NODE";
            break;
        }
        default: {
            oss << "UNKNOWN_NODE";
            break;
        }
    }
}

void WindowSceneLayoutManager::GetRSNodeTreeInfo(const std::shared_ptr<RSNode>& rsNode, int32_t depth,
    std::ostringstream& oss)
{
    CHECK_NULL_VOID(rsNode);
    for (int32_t i = 0; i < depth; ++i) {
        oss << "  ";
    }
    oss << "| ";
    GetRSNodeInfo(rsNode, oss);
    auto children = rsNode->GetChildren();
    for (auto child : children) {
        if (auto childPtr = Rosen::RSNodeMap::Instance().GetNode(child)) {
            GetRSNodeTreeInfo(childPtr, depth + 1, oss);
        }
    }
}

void WindowSceneLayoutManager::GetRSNodeInfo(const std::shared_ptr<RSNode>& rsNode,
    std::ostringstream& oss)
{
    CHECK_NULL_VOID(rsNode);
    DumpRSNodeType(rsNode->GetType(), oss);
    oss << "[" + std::to_string(rsNode->GetId()) << "], ";
    if (rsNode->GetType() == Rosen::RSUINodeType::SURFACE_NODE) {
        auto surfaceNode = Rosen::RSNode::ReinterpretCast<Rosen::RSSurfaceNode>(rsNode);
        std::string name = surfaceNode ? surfaceNode->GetName() : "";
        oss << "Name [" << name << "]";
    }
    oss << ", StagingProperties" << rsNode->GetStagingProperties().Dump();
    auto scale = rsNode->GetStagingProperties().GetScale();
    oss << ", Scale: [" << scale[0] << ", " << scale[1] << "]";
    auto translate = rsNode->GetStagingProperties().GetTranslate();
    oss << ", Translate: [" << translate[0] << ", " << translate[1] << ", "
        << rsNode->GetStagingProperties().GetTranslateZ() << "]";

    oss << ", Rotation: " << rsNode->GetStagingProperties().GetRotation();
    oss << ", Alpha: " << rsNode->GetStagingProperties().GetAlpha();
    oss << ", ClipToBounds: " << rsNode->GetStagingProperties().GetClipBounds();
    auto globalGeometry = rsNode->GetGlobalGeometry();
    if (globalGeometry) {
        auto absRect = globalGeometry->GetAbsRect();
        oss << ", globalAbsRect: " << absRect.ToString().c_str();
        auto matrix = globalGeometry->GetAbsMatrix();
        oss << ", globalScale: [ " << matrix.Get(Rosen::Drawing::Matrix::SCALE_X) << ", "
            << matrix.Get(Rosen::Drawing::Matrix::SCALE_Y) << "]";
        oss << ", globalPos: [" << rsNode->GetGlobalPositionX() << ", " << rsNode->GetGlobalPositionY() << "]";
        oss << ", pivot: [" << globalGeometry->GetPivotX() << ", " << globalGeometry->GetPivotY() << "]";
    } else {
        oss << "globalGeometry: [null],";
    }
    auto localGeometry = rsNode->GetLocalGeometry();
    if (localGeometry) {
        auto absRect = localGeometry->GetAbsRect();
        oss << ", localAbsRect: " << absRect.ToString().c_str();
        auto matrix = localGeometry->GetAbsMatrix();
        oss << ", localScale: [" << matrix.Get(Rosen::Drawing::Matrix::SCALE_X) << ", "
            << matrix.Get(Rosen::Drawing::Matrix::SCALE_Y) << "]";
        oss << ", localTrans: [" << matrix.Get(Rosen::Drawing::Matrix::TRANS_X) << ", "
            << matrix.Get(Rosen::Drawing::Matrix::TRANS_Y) << "]";
        oss << ", localPos: [" << localGeometry->GetX() << ", " << localGeometry->GetY() << "]";
    } else {
        oss << "localGeometry: [null],";
    }
    oss << std::endl;
}
} // namespace OHOS::Ace::NG
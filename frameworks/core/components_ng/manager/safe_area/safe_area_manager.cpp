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
#include "safe_area_manager.h"

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG {
SafeAreaInsets GenerateCutOutAreaWithRoot(const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize)
{
    // cutout regions adjacent to edges.
    auto cutoutArea = safeArea;

    if (cutoutArea.top_.IsValid()) {
        cutoutArea.top_.start = 0;
    }
    if (cutoutArea.bottom_.IsValid()) {
        cutoutArea.bottom_.end = rootSize.Height().has_value() ? rootSize.Height().value()
                                                               : PipelineContext::GetCurrentRootHeight();
    }
    if (cutoutArea.left_.IsValid()) {
        cutoutArea.left_.start = 0;
    }
    if (cutoutArea.right_.IsValid()) {
        cutoutArea.right_.end = rootSize.Width().has_value() ? rootSize.Width().value()
                                                             : PipelineContext::GetCurrentRootWidth();
    }
    return cutoutArea;
}

bool SafeAreaManager::IsModeResize()
{
    return keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE ||
           keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE_WITH_CARET;
}

bool SafeAreaManager::IsModeOffset()
{
    return keyboardAvoidMode_ == KeyBoardAvoidMode::OFFSET ||
           keyboardAvoidMode_ == KeyBoardAvoidMode::OFFSET_WITH_CARET;
}

bool SafeAreaManager::CheckCutoutSafeArea(const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize)
{
    return cutoutSafeArea_ != GenerateCutOutAreaWithRoot(safeArea, rootSize);
}

bool SafeAreaManager::UpdateCutoutSafeArea(const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize)
{
    auto safeAreaWithRoot = GenerateCutOutAreaWithRoot(safeArea, rootSize);
    if (cutoutSafeArea_ == safeAreaWithRoot) {
        return false;
    }
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateCutoutSafeArea %s, safeAreaWithRoot %s", safeArea.ToString().c_str(),
        safeAreaWithRoot.ToString().c_str());
    cutoutSafeArea_ = safeAreaWithRoot;
    return true;
}

bool SafeAreaManager::CheckSystemSafeArea(const SafeAreaInsets& safeArea)
{
    return systemSafeArea_ != safeArea;
}

bool SafeAreaManager::UpdateSystemSafeArea(const SafeAreaInsets& safeArea)
{
    if (systemSafeArea_ == safeArea) {
        return false;
    }
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateSystemSafeArea %s", safeArea.ToString().c_str());
    systemSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::CheckNavSafeArea(const SafeAreaInsets& safeArea)
{
    return navSafeArea_ != safeArea;
}

bool SafeAreaManager::UpdateNavSafeArea(const SafeAreaInsets& safeArea)
{
    if (navSafeArea_ == safeArea) {
        return false;
    }
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateNavSafeArea %s", safeArea.ToString().c_str());
    navSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateKeyboardSafeArea(float keyboardHeight, std::optional<uint32_t> rootHeight)
{
    uint32_t bottom;
    auto container = Container::Current();
    if (container && systemSafeArea_.bottom_.IsValid() && !container->IsSceneBoardEnabled()) {
        bottom = systemSafeArea_.bottom_.start;
        ACE_SCOPED_TRACE("calc keyboardRect use systemSafeArea_.bottom_");
    } else {
        bottom = rootHeight.has_value() ? rootHeight.value() : PipelineContext::GetCurrentRootHeight();
    }
    SafeAreaInsets::Inset inset = { .start = bottom - keyboardHeight, .end = bottom };
    if (inset == keyboardInset_) {
        return false;
    }
    keyboardInset_ = inset;
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateKeyboardSafeArea %s", inset.ToString().c_str());
    return true;
}

bool SafeAreaManager::UpdateKeyboardWebSafeArea(float keyboardHeight, std::optional<uint32_t> rootHeight)
{
    uint32_t bottom;
    auto container = Container::Current();
    if (container && systemSafeArea_.bottom_.IsValid() && !container->IsSceneBoardEnabled()) {
        bottom = systemSafeArea_.bottom_.start;
        ACE_SCOPED_TRACE("calc keyboardWebRect use systemSafeArea_.bottom_");
    } else {
        bottom = rootHeight.has_value() ? rootHeight.value() : PipelineContext::GetCurrentRootHeight();
    }
    SafeAreaInsets::Inset inset = { .start = bottom - keyboardHeight, .end = bottom };
    if (inset == keyboardWebInset_) {
        return false;
    }
    keyboardWebInset_ = inset;
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateKeyboardWebSafeArea %s", inset.ToString().c_str());
    return true;
}

SafeAreaInsets SafeAreaManager::GetCombinedSafeArea(const SafeAreaExpandOpts& opts) const
{
    SafeAreaInsets res;
    if (!IsSafeAreaValid()) {
        return {};
    }
    if ((opts.type & SAFE_AREA_TYPE_CUTOUT) && useCutout_) {
        res = res.Combine(cutoutSafeArea_);
    }
    if (opts.type & SAFE_AREA_TYPE_SYSTEM) {
        res = res.Combine(systemSafeArea_).Combine(navSafeArea_);
    }
    if (keyboardAvoidMode_ == KeyBoardAvoidMode::NONE) {
        return res;
    }
    if ((keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE ||
        keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE_WITH_CARET) && (opts.type & SAFE_AREA_TYPE_KEYBOARD)) {
        res.bottom_ = res.bottom_.Combine(keyboardInset_);
    }
    return res;
}

bool SafeAreaManager::UpdateScbSystemSafeArea(const SafeAreaInsets& safeArea)
{
    if (scbSystemSafeArea_.has_value() && scbSystemSafeArea_.value() == safeArea) {
        return false;
    }
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateScbSystemSafeArea %s", safeArea.ToString().c_str());
    scbSystemSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateScbCutoutSafeArea(const SafeAreaInsets& safeArea, NG::OptionalSize<uint32_t> rootSize)
{
    auto safeAreaWithRoot = GenerateCutOutAreaWithRoot(safeArea, rootSize);
    if (scbCutoutSafeArea_.has_value() && scbCutoutSafeArea_.value() == safeAreaWithRoot) {
        return false;
    }
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateScbCutoutSafeArea %s", safeAreaWithRoot.ToString().c_str());
    scbCutoutSafeArea_ = safeAreaWithRoot;
    return true;
}

bool SafeAreaManager::UpdateScbNavSafeArea(const SafeAreaInsets& safeArea)
{
    if (scbNavSafeArea_.has_value() && scbNavSafeArea_.value() == safeArea) {
        return false;
    }
    ACE_SCOPED_TRACE("SafeAreaManager::UpdateScbNavSafeArea %s", safeArea.ToString().c_str());
    scbNavSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::IsSafeAreaValid() const
{
#ifdef PREVIEW
    return !ignoreSafeArea_;
#else
    return !(ignoreSafeArea_ || (!isFullScreen_ && !isNeedAvoidWindow_));
#endif
}

bool SafeAreaManager::SetIsFullScreen(bool value)
{
    if (isFullScreen_ == value) {
        return false;
    }
    isFullScreen_ = value;
    TAG_LOGI(ACE_SAFE_AREA, "SetIsFullScreen %{public}d", isFullScreen_);
    return true;
}

bool SafeAreaManager::SetIsNeedAvoidWindow(bool value)
{
    if (isNeedAvoidWindow_ == value) {
        return false;
    }
    isNeedAvoidWindow_ = value;
    TAG_LOGI(ACE_SAFE_AREA, "SetIsNeedAvoidWindow %{public}d", isNeedAvoidWindow_);
    return true;
}

bool SafeAreaManager::SetIgnoreSafeArea(bool value)
{
    if (ignoreSafeArea_ == value) {
        return false;
    }
    ignoreSafeArea_ = value;
    TAG_LOGI(ACE_SAFE_AREA, "SetIgnoreSafeArea %{public}d", ignoreSafeArea_);
    return true;
}

bool SafeAreaManager::SetKeyBoardAvoidMode(KeyBoardAvoidMode value)
{
    if (keyboardAvoidMode_ == value) {
        return false;
    }
    if (keyboardAvoidMode_ == KeyBoardAvoidMode::NONE || value == KeyBoardAvoidMode::NONE) {
        keyboardOffset_ = 0.0f;
    }
    keyboardAvoidMode_ = value;
    keyboardSafeAreaEnabled_ = keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE
        || keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE_WITH_CARET;
    TAG_LOGI(ACE_SAFE_AREA, "SetKeyBoardAvoidMode %{public}d", keyboardAvoidMode_);
    return true;
}

KeyBoardAvoidMode SafeAreaManager::GetKeyBoardAvoidMode()
{
    return keyboardAvoidMode_;
}

bool SafeAreaManager::SetIsAtomicService(bool value)
{
    if (isAtomicService_ == value) {
        return false;
    }
    isAtomicService_ = value;
    TAG_LOGI(ACE_SAFE_AREA, "SetIsAtomicService %{public}d", isAtomicService_);
    return true;
}

bool SafeAreaManager::IsAtomicService() const
{
    return isAtomicService_;
}

SafeAreaInsets SafeAreaManager::GetSystemSafeArea() const
{
    if (windowTypeConfig_.isSceneBoardWindow && scbSystemSafeArea_.has_value()) {
        return scbSystemSafeArea_.value();
    }
    return systemSafeArea_;
}

SafeAreaInsets SafeAreaManager::GetCutoutSafeArea() const
{
    if (IsSafeAreaValid() && useCutout_) {
        if (windowTypeConfig_.isSceneBoardWindow && scbCutoutSafeArea_.has_value()) {
            return scbCutoutSafeArea_.value();
        }
        return cutoutSafeArea_;
    }
    return {};
}

SafeAreaInsets SafeAreaManager::GetCutoutSafeAreaWithoutProcess() const
{
    if (windowTypeConfig_.isSceneBoardWindow && scbCutoutSafeArea_.has_value()) {
        return scbCutoutSafeArea_.value();
    }
    return cutoutSafeArea_;
}

SafeAreaInsets SafeAreaManager::GetSafeArea() const
{
    if (!IsSafeAreaValid()) {
        return {};
    }
    auto cutoutSafeArea = useCutout_ ? cutoutSafeArea_ : SafeAreaInsets();
    return systemSafeArea_.Combine(cutoutSafeArea).Combine(navSafeArea_);
}

SafeAreaInsets SafeAreaManager::GetSafeAreaWithoutCutout() const
{
    if (!IsSafeAreaValid()) {
        return {};
    }
    return systemSafeArea_.Combine(navSafeArea_);
}

SafeAreaInsets SafeAreaManager::GetSafeAreaWithoutProcess() const
{
    auto cutoutSafeArea = useCutout_ ? cutoutSafeArea_ : SafeAreaInsets();
    if (!windowTypeConfig_.isSceneBoardWindow) {
        return systemSafeArea_.Combine(cutoutSafeArea).Combine(navSafeArea_);
    }
    SafeAreaInsets scbSafeArea;
    if (scbSystemSafeArea_.has_value()) {
        scbSafeArea = scbSafeArea.Combine(scbSystemSafeArea_.value());
    }
    if (scbCutoutSafeArea_.has_value() && useCutout_) {
        scbSafeArea = scbSafeArea.Combine(scbCutoutSafeArea_.value());
    }
    if (scbNavSafeArea_.has_value()) {
        scbSafeArea = scbSafeArea.Combine(scbNavSafeArea_.value());
    }
    return scbSafeArea;
}

PaddingPropertyF SafeAreaManager::SafeAreaToPadding(bool withoutProcess, LayoutSafeAreaType ignoreType)
{
    if (!withoutProcess) {
#ifdef PREVIEW
        if (ignoreSafeArea_) {
            return {};
        }
#else
        if (ignoreSafeArea_ || (!isFullScreen_ && !isNeedAvoidWindow_)) {
            return {};
        }
#endif
    }
    SafeAreaInsets combinedSafeArea;
    auto cutoutSafeArea = useCutout_ ? cutoutSafeArea_ : SafeAreaInsets();

    bool includeSystem = ignoreType & LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    bool includeKeyboard = ignoreType & LAYOUT_SAFE_AREA_TYPE_KEYBOARD;

    if (includeSystem) {
        combinedSafeArea = systemSafeArea_.Combine(cutoutSafeArea).Combine(navSafeArea_);
    }
    if (includeKeyboard) {
        if (IsModeResize()) {
            combinedSafeArea.bottom_ = combinedSafeArea.bottom_.Combine(keyboardInset_);
        } else if (IsModeOffset()) {
            auto keyboardHeight = keyboardInset_.Length();
            auto bottomLength = GetSafeArea().bottom_.Length();
            auto distance = bottomLength - GetKeyboardOffset(withoutProcess);
            if (GreatNotEqual(keyboardHeight, 0.0f) && distance <= keyboardHeight) {
                combinedSafeArea.bottom_ = GetSafeArea().bottom_;
            }
        }
    }

    PaddingPropertyF result;
    if (combinedSafeArea.left_.IsValid()) {
        result.left = combinedSafeArea.left_.Length();
    }
    if (combinedSafeArea.top_.IsValid()) {
        result.top = combinedSafeArea.top_.Length();
    }
    if (combinedSafeArea.right_.IsValid()) {
        result.right = combinedSafeArea.right_.Length();
    }
    if (combinedSafeArea.bottom_.IsValid()) {
        result.bottom = combinedSafeArea.bottom_.Length();
    }
    return result;
}

float SafeAreaManager::GetKeyboardOffset(bool withoutProcess) const
{
    if (withoutProcess) {
        return keyboardOffset_;
    }
    if (keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE ||
        keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE_WITH_CARET ||
        keyboardAvoidMode_ == KeyBoardAvoidMode::NONE) {
        return 0.0f;
    }
    return keyboardOffset_;
}

OffsetF SafeAreaManager::GetWindowWrapperOffset()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowManager = pipelineContext->GetWindowManager();
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        auto wrapperOffset = OffsetF(static_cast<float>((CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx()),
            static_cast<float>((pipelineContext->GetCustomTitleHeight() + CONTAINER_BORDER_WIDTH).ConvertToPx()));
        return wrapperOffset;
    }
    return OffsetF();
}

void SafeAreaManager::ExpandSafeArea()
{
    ACE_SCOPED_TRACE("ExpandSafeArea node count %zu, IsSafeAreaValid: %d, ignoreSafeArea: %d, isFullScreen: %d, "
                     "isNeedAvoidWindow %d",
        needExpandNodes_.size(), IsSafeAreaValid(), ignoreSafeArea_, isFullScreen_, isNeedAvoidWindow_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    auto iter = needExpandNodes_.begin();
    while (iter != needExpandNodes_.end()) {
        auto frameNode = (*iter).Upgrade();
        if (frameNode) {
            manager->AddGeoRestoreNode(frameNode);
            frameNode->ExpandSafeArea();
        }
        ++iter;
    }
    ClearNeedExpandNode();
}

bool SafeAreaManager::AddNodeToExpandListIfNeeded(const WeakPtr<FrameNode>& node)
{
    if (needExpandNodes_.find(node) == needExpandNodes_.end()) {
        AddNeedExpandNode(node);
        return true;
    }
    return false;
}

std::vector<WeakPtr<FrameNode>> SafeAreaManager::GetExpandNodeSet()
{
    // To isolate set comparator, use vector to collect a copy of nodes
    std::vector<WeakPtr<FrameNode>> result;
    std::copy(needExpandNodes_.begin(), needExpandNodes_.end(), std::back_inserter(result));
    return result;
}

void SafeAreaManager::SetKeyboardInfo(float height)
{
    keyboardOrientation_ = -1;
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    auto keyboardOrientation = static_cast<int32_t>(displayInfo->GetRotation());
    ACE_LAYOUT_SCOPED_TRACE("SetKeyboardInfo keyboardOrientation %d, rawKeyboardHeight %f",
        keyboardOrientation, height);
    SetRawKeyboardHeight(height);
    keyboardOrientation_ = keyboardOrientation;
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->OnRawKeyboardChangedCallback();
}

bool SafeAreaManager::CheckPageNeedAvoidKeyboard(const RefPtr<FrameNode>& frameNode)
{
    if (frameNode->GetTag() != V2::PAGE_ETS_TAG) {
        return false;
    }
    // page will not avoid keyboard when lastChild is sheet
    RefPtr<OverlayManager> overlay;
    if (frameNode->RootNodeIsPage()) {
        auto pattern = frameNode->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pattern, true);
        overlay = pattern->GetOverlayManager();
    } else {
        auto navNode = FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, frameNode->GetRootNodeId());
        CHECK_NULL_RETURN(navNode, true);
        auto pattern = navNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(pattern, true);
        overlay = pattern->GetOverlayManager();
    }
    CHECK_NULL_RETURN(overlay, true);
    return overlay->CheckPageNeedAvoidKeyboard();
}
} // namespace OHOS::Ace::NG

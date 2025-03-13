/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_V2_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_V2_H
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"

namespace OHOS::Ace::NG {
class XComponentPatternV2 : public XComponentPattern {
    DECLARE_ACE_TYPE(XComponentPatternV2, XComponentPattern);
public:
    XComponentPatternV2() = default;
    XComponentPatternV2(XComponentType type, XComponentNodeType nodeType);
    ~XComponentPatternV2() override = default;
    void SetSurfaceHolder(OH_ArkUI_SurfaceHolder* surfaceHolder);
    OH_ArkUI_SurfaceHolder* GetSurfaceHolder();
    int32_t Initialize();
    int32_t Finalize();
    int32_t SetAutoInitialize(bool autoInitialize);
    int32_t IsInitialized(bool& isInitialized);

    bool IsCreateSurfaceHolderForbidden()
    {
        return (hasGotNativeXComponent_ || usesSuperMethod_);
    }

    XComponentNodeType GetXComponentNodeType() const
    {
        return nodeType_;
    }

    bool IsBindNative() override
    {
        return true;
    }

private:
    void OnAttachToFrameNode() override;
    void OnAttachToMainTree() override;
    void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;
    void OnDetachFromMainTree() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void OnRebuildFrame() override;
    void OnModifyDone() override;
    void DumpInfo() override;

    void InitSurface();
    int32_t HandleSurfaceCreated();
    int32_t HandleSurfaceDestroyed();
    void InitializeRenderContext();
    std::pair<bool, bool> UpdateSurfaceRect();
    void HandleSurfaceChangeEvent(bool offsetChanged, bool sizeChanged, bool frameOffsetChange);
    void XComponentSizeChange(const RectF& surfaceRect);
    void OnSurfaceChanged(const RectF& surfaceRect);

    void UpdateUsesSuperMethod()
    {
        if (usesSuperMethod_) {
            return;
        }
        usesSuperMethod_ = (isCNode_ && !isLifecycleInterfaceCalled_ && !surfaceHolder_);
    }

    bool autoInitialize_ = true;
    bool isInitialized_ = false;
    bool isLifecycleInterfaceCalled_ = false;
    bool usesSuperMethod_ = false;
    bool needNotifySizeChanged_ = false;
    OH_ArkUI_SurfaceHolder* surfaceHolder_ = nullptr;
    XComponentNodeType nodeType_ = XComponentNodeType::UNKNOWN;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_PATTERN_V2_H

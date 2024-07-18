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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H

#include "core/components_ng/base/extension_handler.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {

class ExtensionCompanionNode : public ExtensionHandler {
    DECLARE_ACE_TYPE(ExtensionCompanionNode, ExtensionHandler);

public:
    ExtensionCompanionNode(int peerId, int flags, void* peer)
        : peerId_(peerId), flags_(flags), peer_(peer)
    {}

    ~ExtensionCompanionNode() = default;

    ArkUI_Int32 GetPeerId() const;
    ArkUI_Int32 GetCallbackId() const;
    void SetCallbackId(ArkUIVMContext context, int id);

    void SetAlignmentValue(ArkUI_Int32 value)
    {
        alignment_ = value;
    }
    ArkUI_Int32 GetAlignmentValue() const
    {
        return alignment_;
    }

    void SetFlags(ArkUI_Uint32 flags)
    {
        flags_ = flags;
    }

    ArkUI_Uint32 GetFlags() const
    {
        return flags_;
    }

    void SetPeer(void* peer)
    {
        peer_ = peer;
    }

    bool HasCustomerMeasure() const override;
    bool HasCustomerLayout() const override;
    bool NeedRender() const override;

    void SetExtraParam(ArkUI_Int32 type, void* extraParam);
    ArkUI_Int64 GetExtraParam(ArkUI_Int32 type);
    void EraseExtraParam(ArkUI_Int32 type);

protected:
    // FrameNode measure, layout, draw process stump function.
    // call InnerMeasure InnerLayout InnerDraw to process origin logic.
    void OnMeasure(const ExtensionLayoutConstraint& layoutConstraint) override;
    void OnLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY) override;
    void OnForegroundDraw(DrawingContext& context) override;
    void OnDraw(DrawingContext& context) override;
    void OnOverlayDraw(DrawingContext& context) override;

private:
    ArkUI_Int32 peerId_ = 0;
    ArkUI_Int32 customCallbackId_ = 0;
    ArkUI_Uint32 flags_ = 0;
    void* peer_ = nullptr;
    ArkUIVMContext context_ = nullptr;
    ArkUI_Int32 alignment_ = 0;

    ArkUICanvasHandle GetCanvas();
    ArkUIEventCallbackArg Arg(ArkUI_Float32 f32);
    ArkUIEventCallbackArg Arg(ArkUI_Int32 i32);

    std::unordered_map<ArkUI_Int32, void*> extraParamMap_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H
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
#ifndef OHOS_ACE_FRAMEWORK_CJ_CUSTOMDIALOG_CONTROLLER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_CUSTOMDIALOG_CONTROLLER_FFI_H

#include <cinttypes>
#include <optional>
#include <string>

#include "bridge/cj_frontend/cppview/native_view.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/dialog/dialog_component.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model.h"
#include "ffi_remote_data.h"
#include "cj_animate_param_ffi.h"

extern "C" {
struct NativeCustomDialogControllerOptions {
    void(*cancel)();
    bool autoCancel;
    int32_t alignment;
    NativeOffset offset;
    bool customStyle;
    NativeOptionInt32 gridCount;
    uint32_t maskColor;
    NativeRectangle maskRect;
    NativeOptionAnimateParam openAnimation;
    NativeOptionAnimateParam closeAnimation;
    bool showInSubWindow;
    NativeOptionUInt32 backgroundColor;
    NativeLength cornerRadius;
};

CJ_EXPORT int64_t FfiOHOSAceFrameworkCustomDialogControllerCtor(NativeCustomDialogControllerOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkCustomDialogControllerBindView(int64_t controllerId, int64_t nativeViewId);
CJ_EXPORT void FfiOHOSAceFrameworkCustomDialogControllerSetBuilder(int64_t controllerId, void(*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkCustomDialogControllerOpen(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkCustomDialogControllerClose(int64_t id);
}

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeCustomDialogController : public OHOS::FFI::FFIData, public virtual AceType {
    DECLARE_ACE_TYPE(NativeCustomDialogController, AceType)
public:
    NativeCustomDialogController(NativeCustomDialogControllerOptions options);

    void SetView(NativeView* view)
    {
        ownerView_ = view;
    };

    void OpenDialog();

    void CloseDialog();

    void SetBuilder(std::function<void()> builderFunc)
    {
        builderFunction_ = builderFunc;
    };

private:

    NativeView* ownerView_ = nullptr;
    bool isShown_ = false;
    bool pending_ = false;
    // NG
    std::vector<WeakPtr<AceType>> dialogs_;

    DialogProperties dialogProperties_;
    std::function<void()> builderFunction_;
    std::function<void()> cancelFunction_;
    RefPtr<AceType> customDialog_;
    RefPtr<AceType> dialogComponent_;
    RefPtr<AceType> refself_;
    std::list<DialogOperation> dialogOperation_;
};
} // namespace OHOS::Ace::Framework

#endif // OHOS_ACE_FRAMEWORK_CJ_CUSTOMDIALOG__CONTROLLER_FFI_H
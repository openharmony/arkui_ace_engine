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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_native_view_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/native_view.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::FFI;

extern "C" {
void FfiOHOSAceFrameworkThrowNativeError(const char* msg)
{
    LOGE("CJ stack error: %{public}s", msg);
}

void FfiOHOSAceFrameworkNativeLog(const char* msg)
{
    LOGI("CJ log: %{public}s", msg);
}

bool FfiOHOSAceFrameworkLoadNativeView(int64_t nativeViewID)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewID);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkLoadNativeView fail, no NativeView of %{public}" PRId64 ".", nativeViewID);
        return false;
    }
    return LoadNativeView(nativeView);
}

ExternalString FfiOHOSAceFrameworkProcessViewId(int64_t nativeViewId)
{
    auto id = GetProcessViewId(nativeViewId);
    // free memory by cj
    return Utils::MallocCString(id);
}

void FfiOHOSAceFrameworkNativeViewCreate(int64_t nativeViewID)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewID);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkNativeViewCreate fail, no NativeView of %{public}" PRId64 ".", nativeViewID);
        return;
    }
    NativeView::Create(nativeView);
}

int64_t FfiOHOSAceFrameworkNativeViewCtor(int64_t remoteId)
{
    auto remoteView = RemoteData::Create<RemoteView>(remoteId);
    auto view = FFIData::Create<NativeView>(remoteView);
    if (view == nullptr) {
        return FFI_ERROR_CODE;
    }
    return view->GetID();
}

void FfiOHOSAceFrameworkNativeViewDestroy(int64_t id)
{
    auto view = FFIData::GetData<NativeView>(id);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewDestroy fail, no NativeView of %{public}" PRId64 ".", id);
        return;
    }
    view->Destroy();
}

void FfiOHOSAceFrameworkNativeViewMarkNeedUpdate(int64_t nativeViewId)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewId);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkNativeViewMarkNeedUpdate fail, no NativeView of %{public}" PRId64 ".", nativeViewId);
        return;
    }
    nativeView->MarkNeedUpdate();
}

bool FfiOHOSAceFrameworkNativeViewNeedsUpdate(int64_t nativeViewId)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewId);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkNativeViewNeedsUpdate fail, no NativeView of %{public}" PRId64 ".", nativeViewId);
        return false;
    }
    return nativeView->NeedsUpdate();
}

bool FfiOHOSAceFrameworkNativeViewIsFirstRender(int64_t nativeViewId)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewId);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkNativeViewIsFirstRender fail, no NativeView of %{public}" PRId64 ".", nativeViewId);
        return false;
    }
    return nativeView->IsFirstRender();
}

void FfiOHOSAceFrameworkNativeViewMarkStatic(int64_t nativeViewId)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewId);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkNativeViewMarkStatic fail, no NativeView of %{public}" PRId64 ".", nativeViewId);
        return;
    }
    nativeView->MarkStatic();
}

bool FfiOHOSAceFrameworkNativeViewIsStatic(int64_t nativeViewId)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewId);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkNativeViewIsStatic fail, no NativeView of %{public}" PRId64 ".", nativeViewId);
        return false;
    }
    return nativeView->IsStatic();
}

void FfiOHOSAceFrameworkNativeViewSyncInstanceId(int64_t nativeViewId)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewSyncInstanceId fail, no NativeView of %{public}" PRId64, nativeViewId);
        return;
    }
    view->SyncInstanceId();
}

void FfiOHOSAceFrameworkNativeViewRestoreInstanceId(int64_t nativeViewId)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewRestoreInstanceId fail, no NativeView of %{public}" PRId64, nativeViewId);
        return;
    }
    view->RestoreInstanceId();
}

void FfiOHOSAceFrameworkNativeViewFinishUpdateFunc(int64_t nativeViewId, int64_t elmtId)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewFinishUpdateFunc fail, no NativeView of %{public}" PRId64, nativeViewId);
        return;
    }
    view->FinishUpdateFunc(elmtId);
}

int32_t FfiOHOSAceFrameworkNativeViewGetUINodeId(int64_t nativeViewId)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewGetUINodeId fail, no NativeView of %{public}" PRId64, nativeViewId);
        return -1;
    }
    auto node = view->GetViewNode();
    if (!node) {
        return -1;
    }
    auto uiNode = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::UINode>(node);
    if (!uiNode) {
        return -1;
    }
    return uiNode->GetId();
}

void FfiOHOSAceFrameworkViewDeletedElmtIdsHaveBeenPurged(int64_t nativeViewId, VectorCJInt64Handle vec)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkViewDeletedElmtIdsHaveBeenPurged fail, no NativeView of %{public}" PRId64,
            nativeViewId);
        return;
    }

    auto cjRectangleVec = *reinterpret_cast<std::vector<int64_t>*>(vec);

    std::vector<int64_t> result;
    for (size_t i = 0; i < cjRectangleVec.size(); i++) {
        result.emplace_back(cjRectangleVec[i]);
    }

    view->DeletedElmtIdsHaveBeenPurged(result);
}

VectorToCFFIArray FfiOHOSAceFrameworkViewGetDeletedElemtIds(int64_t nativeViewId)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkViewGetDeletedElemtIds fail, no NativeView of %{public}" PRId64, nativeViewId);
        return VectorToCFFIArray();
    }

    std::vector<int64_t> result;
    view->GetDeletedElemtIds(result);

    auto temp = (int64_t*)malloc(sizeof(int64_t) * result.size());
    if (temp == NULL) {
        LOGE("FfiOHOSAceFrameworkViewGetDeletedElemtIds fail, malloc fail");
        return VectorToCFFIArray();
    }
    VectorToCFFIArray res { .size = result.size(), .buffer = temp, .free = reinterpret_cast<void (*)(int64_t*)>(free) };

    for (size_t i = 0; i < result.size(); i++) {
        res.buffer[i] = result[i];
    }
    return res;
}

VectorCJInt64Handle FFICJCreateVectorCJInt64(int64_t size)
{
    return new std::vector<int64_t>(size);
}

void FFICJVectorCJInt64SetElement(VectorCJInt64Handle vec, int64_t index, int64_t value)
{
    auto actualVec = reinterpret_cast<std::vector<int64_t>*>(vec);
    (*actualVec)[index] = value;
}

void FFICJVectorCJInt64Delete(VectorCJInt64Handle vec)
{
    auto actualVec = reinterpret_cast<std::vector<int64_t>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkNativeViewCreateRecycle(
    int64_t nativeViewId, bool isRecycling, const char* name, void (*callback)())
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewCreateRecycle fail, no NativeView of %{public}" PRId64, nativeViewId);
        return;
    }
    auto func = CJLambda::Create(callback);
    NativeView::CreateRecycle(view, isRecycling, name, std::move(func));
}

void FfiOHOSAceFrameworkNativeViewResetRecycleCustomNode(int64_t nativeViewId)
{
    auto view = FFIData::GetData<NativeView>(nativeViewId);
    if (!view) {
        LOGE("FfiOHOSAceFrameworkNativeViewResetRecycleCustomNode fail, no NativeView of %{public}" PRId64,
            nativeViewId);
        return;
    }
    view->ResetRecycleCustomNode();
}
}

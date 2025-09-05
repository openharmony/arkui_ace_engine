/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include "core/components_ng/manager/display_sync/ui_display_sync.h"

namespace OHOS::Ace::Ani {
namespace {
const char* DISPLAY_SYNC_CLASS_NAME = "@ohos.graphics.displaySync.displaySync.DisplaySync";
ani_ref gDisplaySyncCls {};
ani_method gDisplaySyncCtor {};
ani_field gDisplaySyncLongField {};
const char* INTERVAL_INFO_CLASS_NAME = "@ohos.graphics.displaySync.displaySync.IntervalInfo";
ani_ref gIntervalInfoCls {};
ani_method gIntervalInfoCtor {};
const char* EXPECTED_FRAME_RATE_RANGE_CLASS_NAME = "arkui.component.common.ExpectedFrameRateRange";
ani_ref gExpectedFrameRateRangeCls {};
ani_method gGetMin {};
ani_method gGetMax {};
ani_method gGetExpected {};
constexpr int EXPECTED_FRAME_RATE_RANGE_ERROR_CODE = 401;
const char* CLEANER_CLASS_NAME = "@ohos.graphics.displaySync.displaySync.Cleaner";
ani_ref gCleanerCls {};
ani_field gCleanerPtrField {};
}

class DisplaySync final {
public:
    DisplaySync() = delete;
    explicit DisplaySync(RefPtr<UIDisplaySync>& uiDisplaySync)
        : uiDisplaySync_(uiDisplaySync) {}

    ~DisplaySync()
    {
        if (uiDisplaySync_) {
            uiDisplaySync_->DelFromPipelineOnContainer();
        }
    }

    RefPtr<UIDisplaySync> GetUIDisplaySync() const
    {
        return uiDisplaySync_;
    }

    ani_ref GetOnframeRef() const
    {
        return onFrameRef_;
    }

    void SetOnframeRef(const ani_ref& onframe)
    {
        onFrameRef_ = onframe;
    }

    ani_ref onFrameRef_ = nullptr;

private:
    RefPtr<UIDisplaySync> uiDisplaySync_;
};

ani_object WrapStsError(ani_env* env, const std::string &msg)
{
    ani_class cls {};
    ani_method method {};
    ani_object obj = nullptr;
    ani_status status = ANI_ERROR;
    if (env == nullptr) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "null env");
        return nullptr;
    }

    ani_string aniMsg = nullptr;
    if ((status = env->String_NewUTF8(msg.c_str(), msg.size(), &aniMsg)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "Error String_NewUTF8 failed %{public}d", status);
        return nullptr;
    }

    ani_ref undefRef;
    if ((status = env->GetUndefined(&undefRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "Error GetUndefined failed %{public}d", status);
        return nullptr;
    }

    if ((status = env->FindClass("escompat.Error", &cls)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "Error FindClass failed %{public}d", status);
        return nullptr;
    }
    if ((status = env->Class_FindMethod(
        cls, "<ctor>", "C{std.core.String}C{escompat.ErrorOptions}:", &method)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "Error Class_FindMethod failed %{public}d", status);
        return nullptr;
    }

    if ((status = env->Object_New(cls, method, &obj, aniMsg, undefRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "Error Object_New failed %{public}d", status);
        return nullptr;
    }
    return obj;
}

ani_object CreateError(ani_env* env, ani_int code, const std::string& msg)
{
    ani_class cls {};
    ani_method method {};
    ani_object obj = nullptr;
    ani_status status = ANI_ERROR;
    if (env == nullptr) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "null env");
        return nullptr;
    }
    if ((status = env->FindClass("@ohos.base.BusinessError", &cls)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "BusinessError FindClass failed %{public}d", status);
        return nullptr;
    }
    if ((status = env->Class_FindMethod(cls, "<ctor>", "iC{escompat.Error}:", &method)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "BusinessError Class_FindMethod failed %{public}d", status);
        return nullptr;
    }
    ani_object error = WrapStsError(env, msg);
    if (error == nullptr) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "BusinessError error null");
        return nullptr;
    }
    ani_int dCode(code);
    if ((status = env->Object_New(cls, method, &obj, dCode, error)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, " BusinessError Object_New failed %{public}d", status);
        return nullptr;
    }
    return obj;
}

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1);
    char *utf8Buffer = buffer.data();

    ani_size bytesWritten = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytesWritten);
    utf8Buffer[bytesWritten] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

void ParseExpectedFrameRateRange(ani_env* env, ani_object objOption,
    FrameRateRange& frameRateRange)
{
    ani_boolean isInstance;
    if (ANI_OK != env->Object_InstanceOf(
        objOption, static_cast<ani_class>(gExpectedFrameRateRangeCls), &isInstance)) {
        return;
    }

    ani_double minAni;
    ani_double maxAni;
    ani_double expectedAni;
    if (ANI_OK != env->Object_CallMethod_Double(objOption, gGetMin, &minAni)) {
        return;
    }
    if (ANI_OK != env->Object_CallMethod_Double(objOption, gGetMax, &maxAni)) {
        return;
    }
    if (ANI_OK != env->Object_CallMethod_Double(objOption, gGetExpected, &expectedAni)) {
        return;
    }
    frameRateRange.min_ = static_cast<int32_t>(minAni);
    frameRateRange.max_ = static_cast<int32_t>(maxAni);
    frameRateRange.preferred_ = static_cast<int32_t>(expectedAni);
    if (!frameRateRange.IsValid()) {
        ani_object error = CreateError(env, EXPECTED_FRAME_RATE_RANGE_ERROR_CODE, "ExpectedFrameRateRange error");
        if (error != nullptr) {
            env->ThrowError(static_cast<ani_error>(error));
        }
    }
}

static DisplaySync *GetDisplaySync(ani_env* env, ani_object obj)
{
    ani_long displaySync;
    if (ANI_OK != env->Object_GetField_Long(obj, gDisplaySyncLongField, &displaySync)) {
        return nullptr;
    }
    return reinterpret_cast<DisplaySync*>(displaySync);
}

static RefPtr<UIDisplaySync> GetUIDisplaySync(ani_env* env, ani_object obj)
{
    auto displaySync = GetDisplaySync(env, obj);
    if (displaySync == nullptr) {
        return nullptr;
    }
    auto uiDisplaySync = displaySync->GetUIDisplaySync();
    if (uiDisplaySync == nullptr) {
        return nullptr;
    }
    return uiDisplaySync;
}

ani_object createIntervalInfo(ani_env* env, int64_t timestamp, int64_t targetTimestamp)
{
    ani_object intervalInfoObj;
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gIntervalInfoCls),
        gIntervalInfoCtor, &intervalInfoObj, ani_long(timestamp), ani_long(targetTimestamp))) {
        return nullptr;
    }
    return intervalInfoObj;
}

static void JSOnFrame_On(ani_env* env, ani_object obj, ani_string callbackType, ani_object callbackObj)
{
    if (ANIUtils_ANIStringToStdString(env, callbackType) != "frame") {
        return;
    }
    auto displaySync = GetDisplaySync(env, obj);
    if (displaySync == nullptr) {
        return;
    }
    if (displaySync->GetOnframeRef()) {
        return;
    }
    auto uiDisplaySync = displaySync->GetUIDisplaySync();
    if (uiDisplaySync == nullptr) {
        return;
    }

    ani_ref onFrameRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onFrameGlobalRef;
    env->GlobalReference_Create(onFrameRef, &onFrameGlobalRef);
    displaySync->SetOnframeRef(onFrameGlobalRef);
    uiDisplaySync->RegisterOnFrameWithData([env, onFrameGlobalRef] (RefPtr<DisplaySyncData> displaySyncData) {
        auto fnObj = reinterpret_cast<ani_fn_object>(onFrameGlobalRef);
        ani_ref result;
        ani_object intervalInfo = createIntervalInfo(
            env, displaySyncData->timestamp_, displaySyncData->targetTimestamp_);
        if (intervalInfo == nullptr) {
            return;
        }
        std::vector<ani_ref> tmp = { reinterpret_cast<ani_ref>(intervalInfo) };
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    });
}

static void JSOnFrame_Off(ani_env* env, ani_object obj, ani_string callbackType, ani_object callbackObj)
{
    if (ANIUtils_ANIStringToStdString(env, callbackType) != "frame") {
        return;
    }
    auto displaySync = GetDisplaySync(env, obj);
    if (displaySync == nullptr) {
        return;
    }
    auto uiDisplaySync = displaySync->GetUIDisplaySync();
    if (uiDisplaySync == nullptr) {
        return;
    }
    displaySync->SetOnframeRef(nullptr);
    uiDisplaySync->UnregisterOnFrame();
}

static void JSStart(ani_env* env, ani_object obj) {
    if (auto uiDisplaySync = GetUIDisplaySync(env, obj); uiDisplaySync != nullptr) {
        uiDisplaySync->AddToPipelineOnContainer();
    }
}

static void JSStop(ani_env* env, ani_object obj) {
    if (auto uiDisplaySync = GetUIDisplaySync(env, obj); uiDisplaySync != nullptr) {
        uiDisplaySync->DelFromPipelineOnContainer();
    }
}

static void JSSetExpectedFrameRateRange(ani_env* env, ani_object obj, ani_object objOption)
{
    if (auto uiDisplaySync = GetUIDisplaySync(env, obj); uiDisplaySync != nullptr) {
        FrameRateRange frameRateRange;
        ParseExpectedFrameRateRange(env, objOption, frameRateRange);
        uiDisplaySync->SetExpectedFrameRateRange(frameRateRange);
    }
}

ani_object ANICreate(ani_env* env, ani_object object, ani_object aniOption)
{
    ani_object displaySync_obj = {};
    auto uiDisplaySync = AceType::MakeRefPtr<UIDisplaySync>();
    DisplaySync* displaySync = new DisplaySync(uiDisplaySync);
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gDisplaySyncCls),
        gDisplaySyncCtor, &displaySync_obj, reinterpret_cast<ani_long>(displaySync))) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] create displaySync fail");
        delete displaySync;
        return displaySync_obj;
    }
    return displaySync_obj;
}

void DeleteGlobalReference(ani_env* env)
{
    if (gDisplaySyncCls != nullptr) {
        env->GlobalReference_Delete(gDisplaySyncCls);
    }
    if (gIntervalInfoCls != nullptr) {
        env->GlobalReference_Delete(gIntervalInfoCls);
    }
    if (gExpectedFrameRateRangeCls != nullptr) {
        env->GlobalReference_Delete(gExpectedFrameRateRangeCls);
    }
    if (gCleanerCls != nullptr) {
        env->GlobalReference_Delete(gCleanerCls);
    }
}

static void clean([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object) {
    ani_long ptr;
    if (ANI_OK != env->Object_GetField_Long(object, gCleanerPtrField, &ptr)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find clean ptr fail");
        DeleteGlobalReference(env);
        return;
    }
    DeleteGlobalReference(env);
    delete reinterpret_cast<DisplaySync*>(ptr);
}

ani_status BindDisplaySync(ani_env* env)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(DISPLAY_SYNC_CLASS_NAME, &cls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find DisplaySync class fail");
        return ANI_ERROR;
    }
    if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(cls), &gDisplaySyncCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global DisplaySync failed");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"on", nullptr, reinterpret_cast<void*>(JSOnFrame_On)},
        ani_native_function{"off", nullptr, reinterpret_cast<void*>(JSOnFrame_Off)},
        ani_native_function{"start", nullptr, reinterpret_cast<void*>(JSStart)},
        ani_native_function{"stop", nullptr, reinterpret_cast<void*>(JSStop)},
        ani_native_function{"setExpectedFrameRateRange", nullptr,
            reinterpret_cast<void*>(JSSetExpectedFrameRateRange)},
    };
    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] bind native method fail");
        return ANI_ERROR;
    };

    ani_class cleanerCls;
    if (ANI_OK != env->FindClass(CLEANER_CLASS_NAME, &cleanerCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find Cleaner class fail");
        return ANI_ERROR;
    }
    if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(cleanerCls), &gCleanerCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global Cleaner failed");
        return ANI_ERROR;
    }

    std::array cleanerMethods = {
        ani_native_function {"clean", nullptr, reinterpret_cast<void*>(clean) },
    };

    if (ANI_OK != env->Class_BindNativeMethods(cleanerCls, cleanerMethods.data(), cleanerMethods.size())) {
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status CacheDisplaySync(ani_env* env)
{
    if (gDisplaySyncCls != nullptr &&
        ANI_OK != env->Class_FindMethod(static_cast<ani_class>(gDisplaySyncCls),
        "<ctor>", nullptr, &gDisplaySyncCtor)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global DisplaySync Ctor method failed");
        return ANI_ERROR;
    }
    if (ANI_OK != env->Class_FindField(
        static_cast<ani_class>(gDisplaySyncCls), "displaySync", &gDisplaySyncLongField)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global gDisplaySyncLongField failed");
        return ANI_ERROR;
    }
    if (gCleanerCls != nullptr &&
        ANI_OK != env->Class_FindField(static_cast<ani_class>(gCleanerCls), "ptr", &gCleanerPtrField)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global gCleanerPtrField failed");
        return ANI_ERROR;
    }
    return ANI_OK;
}

ani_status CacheIntervalInfo(ani_env* env)
{
    ani_class intervalInfoCls;
    if (ANI_OK != env->FindClass(INTERVAL_INFO_CLASS_NAME, &intervalInfoCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find IntervalInfo class fail");
        return ANI_ERROR;
    }
    if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(intervalInfoCls), &gIntervalInfoCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global IntervalInfo failed");
        return ANI_ERROR;
    }
    if (ANI_OK != env->Class_FindMethod(
        static_cast<ani_class>(gIntervalInfoCls), "<ctor>", "ll:", &gIntervalInfoCtor)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global gIntervalInfoCtor failed");
        return ANI_ERROR;
    }
    return ANI_OK;
}

ani_status CacheExpectedFrameRateRange(ani_env* env)
{
    ani_class expectedFrameRateRangeCls;
    if (ANI_OK != env->FindClass(EXPECTED_FRAME_RATE_RANGE_CLASS_NAME, &expectedFrameRateRangeCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find ExpectedFrameRateRange class fail");
        return ANI_ERROR;
    }
    if (ANI_OK != env->GlobalReference_Create(
        static_cast<ani_ref>(expectedFrameRateRangeCls), &gExpectedFrameRateRangeCls)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global gExpectedFrameRateRangeCls failed");
        return ANI_ERROR;
    }
    if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(gExpectedFrameRateRangeCls),
        "<get>min", nullptr, &gGetMin)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global ExpectedFrameRateRange gGetMin method failed");
        return ANI_ERROR;
    }
    if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(gExpectedFrameRateRangeCls),
        "<get>max", nullptr, &gGetMax)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global ExpectedFrameRateRange gGetMax method failed");
        return ANI_ERROR;
    }
    if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(gExpectedFrameRateRangeCls),
        "<get>expected", nullptr, &gGetExpected)) {
        TAG_LOGE(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Create Global ExpectedFrameRateRange gGetExpected method failed");
        return ANI_ERROR;
    }
    return ANI_OK;
}
}  // namespace OHOS::Ace::Ani

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }
    ani_namespace displaySyncNamespace;
    if (ANI_OK != env->FindNamespace("@ohos.graphics.displaySync.displaySync", &displaySyncNamespace)) {
        return ANI_ERROR;
    }
    std::array staticMethods = {
        ani_native_function {"create", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::Ani::ANICreate)},
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(
        displaySyncNamespace, staticMethods.data(), staticMethods.size())) {
        return ANI_ERROR;
    };

    if (ANI_OK != OHOS::Ace::Ani::BindDisplaySync(env) ||
        ANI_OK != OHOS::Ace::Ani::CacheDisplaySync(env) ||
        ANI_OK != OHOS::Ace::Ani::CacheIntervalInfo(env) ||
        ANI_OK != OHOS::Ace::Ani::CacheExpectedFrameRateRange(env)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DISPLAY_SYNC, "[ANI] DisplaySync init fail");
        OHOS::Ace::Ani::DeleteGlobalReference(env);
        return ANI_ERROR;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}

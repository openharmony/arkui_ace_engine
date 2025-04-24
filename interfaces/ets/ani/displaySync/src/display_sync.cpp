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

std::string ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str)
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

void ParseExpectedFrameRateRange(ani_env *env, ani_object objOption,
    FrameRateRange& frameRateRange)
{
    static const char *className = "L@ohos/graphic/displaySync/ExpectedFrameRateRange;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return;
    }

    ani_boolean isInstance;
    if (ANI_OK != env->Object_InstanceOf(objOption, cls, &isInstance)) {
        return;
    }

    int32_t minFPS = 0;
    int32_t maxFPS = 0;
    int32_t expectedFPS = 0;

    ani_double minAni;
    ani_double maxAni;
    ani_double expectedAni;
    env->Object_GetPropertyByName_Double(objOption, "min", &minAni);
    env->Object_GetPropertyByName_Double(objOption, "max", &maxAni);
    env->Object_GetPropertyByName_Double(objOption, "expected", &expectedAni);

    minFPS = static_cast<int32_t>(minAni);
    maxFPS = static_cast<int32_t>(maxAni);
    expectedFPS = static_cast<int32_t>(expectedAni);
    frameRateRange.Set(minFPS, maxFPS, expectedFPS);
}

static DisplaySync *GetDisplaySync(ani_env *env, ani_object obj)
{
    ani_long displaySync;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "displaySync", &displaySync)) {
        return nullptr;
    }
    return reinterpret_cast<DisplaySync *>(displaySync);
}

static RefPtr<UIDisplaySync> GetUIDisplaySync(ani_env *env, ani_object obj)
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

ani_object createIntervalInfo(ani_env *env, int64_t timestamp, int64_t targetTimestamp)
{
    static const char *className = "L@ohos/graphic/displaySync/IntervalInfo;";
    ani_class intervalInfo_cls;

    if (ANI_OK != env->FindClass(className, &intervalInfo_cls))
    {
        std::cerr << "Not found '" << className << "'" << std::endl;
        return nullptr;
    }
    ani_method intervalInfoCtor;
    env->Class_FindMethod(intervalInfo_cls, "<ctor>", "JJ:V", &intervalInfoCtor);
    ani_object intervalInfoObj;
    env->Object_New(
        intervalInfo_cls, intervalInfoCtor, &intervalInfoObj, ani_long(timestamp), ani_long(targetTimestamp));
    return intervalInfoObj;
}

static void JSOnFrame_On(ani_env *env, ani_object obj, ani_string callbackType, ani_object callbackObj)
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
        auto intervalInfo = createIntervalInfo(env, displaySyncData->timestamp_, displaySyncData->targetTimestamp_);
        std::vector<ani_ref> tmp = { reinterpret_cast<ani_ref>(intervalInfo) };
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    });
}

static void JSOnFrame_Off(ani_env *env, ani_object obj, ani_string callbackType, ani_object callbackObj)
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

static void JSStart(ani_env *env, ani_object obj) {
    if (auto uiDisplaySync = GetUIDisplaySync(env, obj); uiDisplaySync != nullptr) {
        uiDisplaySync->AddToPipelineOnContainer();
    }
}

static void JSStop(ani_env *env, ani_object obj) {
    if (auto uiDisplaySync = GetUIDisplaySync(env, obj); uiDisplaySync != nullptr) {
        uiDisplaySync->DelFromPipelineOnContainer();
    }
}

static void JSSetExpectedFrameRateRange(ani_env *env, ani_object obj, ani_object objOption)
{
    if (auto uiDisplaySync = GetUIDisplaySync(env, obj); uiDisplaySync != nullptr) {
        FrameRateRange frameRateRange;
        ParseExpectedFrameRateRange(env, objOption, frameRateRange);
        uiDisplaySync->SetExpectedFrameRateRange(frameRateRange);
    }
}

ani_object ANICreate(ani_env *env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    ani_object displaySync_obj = {};
    static const char *className = "L@ohos/graphic/displaySync/DisplaySyncResultInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find class fail");
        return displaySync_obj;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] find method fail");
        return displaySync_obj;
    }

    auto uiDisplaySync = AceType::MakeRefPtr<UIDisplaySync>();
    DisplaySync* displaySync = new DisplaySync(uiDisplaySync);
    if (ANI_OK != env->Object_New(cls, ctor, &displaySync_obj, reinterpret_cast<ani_long>(displaySync))) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] create displaySync fail");
        return displaySync_obj;
    }
    return displaySync_obj;
}

ani_status BindDisplaySync(ani_env *env)
{
    static const char *className = "L@ohos/graphic/displaySync/DisplaySync;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Bind DisplaySync fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"create",
            ":L@ohos/graphic/displaySync/DisplaySyncResult;",
            reinterpret_cast<void *>(ANICreate)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] Bind DisplaySync method fail");
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status BindDisplaySyncResult(ani_env *env)
{
    static const char *className = "L@ohos/graphic/displaySync/DisplaySyncResultInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] bind DisplaySyncResultInner result fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"on", nullptr, reinterpret_cast<void *>(JSOnFrame_On)},
        ani_native_function{"off", nullptr, reinterpret_cast<void *>(JSOnFrame_Off)},
        ani_native_function{"start", ":V", reinterpret_cast<void *>(JSStart)},
        ani_native_function{"stop", ":V", reinterpret_cast<void *>(JSStop)},
        ani_native_function{"setExpectedFrameRateRange", nullptr,
            reinterpret_cast<void *>(JSSetExpectedFrameRateRange)},
    };
    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_DISPLAY_SYNC, "[ANI] bind native method fail");
        return ANI_ERROR;
    };
    return ANI_OK;
}
}  // namespace OHOS::Ace::Ani

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_status retBindDisplaySync = OHOS::Ace::Ani::BindDisplaySync(env);
    if (retBindDisplaySync != ANI_OK) {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_DISPLAY_SYNC, "[ANI] BindDisplaySync fail");
        return retBindDisplaySync;
    }
    ani_status retBindResult = OHOS::Ace::Ani::BindDisplaySyncResult(env);
    if (retBindResult != ANI_OK) {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_DISPLAY_SYNC, "[ANI] BindDisplaySyncResult fail");
        return retBindResult;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
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

#include "prompt_action_utils.h"

#include "bridge/common/utils/utils.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/base/error/error_code.h"

namespace OHOS::Ace::Ani {
static const std::unordered_map<int32_t, std::string> ERROR_CODE_TO_MSG {
    { ERROR_CODE_PERMISSION_DENIED, "Permission denied. " },
    { ERROR_CODE_PARAM_INVALID, "Parameter error. " },
    { ERROR_CODE_SYSTEMCAP_ERROR, "Capability not supported. " },
    { ERROR_CODE_INTERNAL_ERROR, "Internal error. " },
    { ERROR_CODE_URI_ERROR, "Uri error. " },
    { ERROR_CODE_PAGE_STACK_FULL, "Page stack error. " },
    { ERROR_CODE_URI_ERROR_LITE, "Uri error. " },
    { ERROR_CODE_DIALOG_CONTENT_ERROR, "Dialog content error. " },
    { ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST, "Dialog content already exist. " },
    { ERROR_CODE_DIALOG_CONTENT_NOT_FOUND, "Dialog content not found. " },
    { ERROR_CODE_TOAST_NOT_FOUND, "Toast not found. " }
};

std::string ErrorToMessage(int32_t code)
{
    auto iter = ERROR_CODE_TO_MSG.find(code);
    return (iter != ERROR_CODE_TO_MSG.end()) ? iter->second : "";
}

std::string GetErrorMsg(int32_t errorCode)
{
    std::string strMsg;
    if (errorCode == ERROR_CODE_DIALOG_CONTENT_ERROR) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ERROR) + "The ComponentContent is incorrect.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) +
            "The ComponentContent has already been opened.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) + "The ComponentContent cannot be found.";
    } else {
        strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Build custom dialog failed.";
    }
    return strMsg;
}


ani_error GetErrorObject(ani_env *env, const std::string &errMsg, int32_t code)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class errClass;
    ani_status status = env->FindClass("L@ohos/base/BusinessError;", &errClass);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "find class failed. status: %{public}d", status);
        return nullptr;
    }
    ani_method ctor;
    status = env->Class_FindMethod(errClass, "<ctor>", ":V", &ctor);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "cannot find constructor for class. status: %{public}d", status);
        return nullptr;
    }
    ani_string errMessage;
    status = env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &errMessage);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "convert string to ani string failed. status: %{public}d", status);
        return nullptr;
    }
    ani_object errObj;
    status = env->Object_New(errClass, ctor, &errObj);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "cannot create ani error object. status: %{public}d", status);
        return nullptr;
    }
    status = env->Object_SetPropertyByName_Int(errObj, "code", static_cast<ani_int>(code));
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "set error code failed. status: %{public}d", status);
        return nullptr;
    }
    status = env->Object_SetPropertyByName_Ref(errObj, "message", errMessage);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "set error message failed. status: %{public}d", status);
        return nullptr;
    }
    return static_cast<ani_error>(errObj);
}

void AniThrow(ani_env *env, const std::string &errMsg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = GetErrorObject(env, errMsg, code);
    if (errObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(errObj)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "throw ani error object failed!");
        return;
    }
}
} // namespace OHOS::Ace::Ani

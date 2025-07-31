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
    if (ANI_OK != env->FindClass("@ohos.base.BusinessError", &errClass)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "find class failed");
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(errClass, "<ctor>", ":", &ctor)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "cannot find constructor for class.");
        return nullptr;
    }
    ani_string errMessage;
    if (ANI_OK != env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &errMessage)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "convert string to ani string failed.");
        return nullptr;
    }
    ani_object errObj;
    if (ANI_OK != env->Object_New(errClass, ctor, &errObj)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "cannot create ani error object.");
        return nullptr;
    }
    if (ANI_OK != env->Object_SetFieldByName_Double(errObj, "code", static_cast<ani_double>(code))) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "set error code failed.");
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(errObj, "message", errMessage)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "set error message failed.");
        return nullptr;
    }
    return static_cast<ani_error>(errObj);
}

void AniThrow(ani_env *env, const std::string &errMsg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = GetErrorObject(env, errMsg, code);
    if (errObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(errObj)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "throw ani error object failed!");
        return;
    }
}
} // namespace OHOS::Ace::Ani
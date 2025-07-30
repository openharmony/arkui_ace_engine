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

#include "ani_utils.h"

#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

std::string AniUtils::ANIStringToStdString(ani_env* env, ani_string aniStr)
{
    CHECK_NULL_RETURN(env, "");
    ani_size strSize;
    ani_status status = ANI_OK;
    if ((status = env->String_GetUTF8Size(aniStr, &strSize)) != ANI_OK) {
        return "";
    }
    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();
    ani_size bytesWritten = 0;
    if ((status = env->String_GetUTF8(aniStr, utf8Buffer, strSize + 1, &bytesWritten)) != ANI_OK) {
        return "";
    }
    utf8Buffer[bytesWritten] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

ani_object AniUtils::CreateDouble(ani_env* env, double value)
{
    CHECK_NULL_RETURN(env, nullptr);
    static const char* className = "std.core.Double";
    ani_class doubleCls;
    if (ANI_OK != env->FindClass(className, &doubleCls)) {
        return nullptr;
    }
    ani_method doubleCtor;
    if (ANI_OK != env->Class_FindMethod(doubleCls, "<ctor>", "d:", &doubleCtor)) {
        return nullptr;
    }
    ani_object doubleObj;
    if (ANI_OK != env->Object_New(doubleCls, doubleCtor, &doubleObj, static_cast<ani_double>(value))) {
        return nullptr;
    }
    return doubleObj;
}

bool AniUtils::GetOptionalDouble(ani_env* env, ani_ref value, double& result)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    if (env->Reference_IsUndefined(value, &isUndefined) != ANI_OK) {
        return false;
    }
    ani_double aniResult;
    if (env->Object_CallMethodByName_Double(static_cast<ani_object>(value), "unboxed", ":d", &aniResult) != ANI_OK) {
        return false;
    }
    result = static_cast<double>(aniResult);
    return true;
}
} // namespace OHOS::Ace::NG

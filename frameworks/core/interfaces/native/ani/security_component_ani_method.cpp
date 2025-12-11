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

#include "security_component_ani_method.h"

#include "core/components_ng/pattern/security_component/security_component_log.h"

namespace OHOS::Ace::NG {
ani_object SecurityComponentAniMethod::CreateDouble(ani_env* env, double value)
{
    CHECK_NULL_RETURN(env, nullptr);
    static const char* className = "std.core.Double";
    ani_class persion_cls;
    ani_status status = env->FindClass(className, &persion_cls);
    if (ANI_OK != status) {
        SC_LOG_ERROR("Find class failed when create double in ani, status: %{public}d.", status);
        return nullptr;
    }
    ani_method infoCtor;
    status = env->Class_FindMethod(persion_cls, "<ctor>", "d:", &infoCtor);
    if (ANI_OK != status) {
        SC_LOG_ERROR("Find method failed when create double in ani, status: %{public}d.", status);
        return nullptr;
    }
    ani_object personInfoObj;
    status = env->Object_New(persion_cls, infoCtor, &personInfoObj, ani_double(value));
    if (ANI_OK != status) {
        SC_LOG_ERROR("New object failed when create double in ani, status: %{public}d.", status);
        return nullptr;
    }
    return personInfoObj;
}

ani_object SecurityComponentAniMethod::CreateInt32(ani_env* env, int32_t value)
{
    CHECK_NULL_RETURN(env, nullptr);
    static const char* className = "std.core.Int";
    ani_class int_cls;
    ani_status status = env->FindClass(className, &int_cls);
    if (ANI_OK != status) {
        SC_LOG_ERROR("Find class failed when create int32 in ani, status: %{public}d.", status);
        return nullptr;
    }
    ani_method intCtor;
    status = env->Class_FindMethod(int_cls, "<ctor>", "i:", &intCtor);
    if (ANI_OK != status) {
        SC_LOG_ERROR("Find method failed when create int32 in ani, status: %{public}d.", status);
        return nullptr;
    }
    ani_object intObj;
    status = env->Object_New(int_cls, intCtor, &intObj, value);
    if (ANI_OK != status) {
        SC_LOG_ERROR("New object failed when create int32 in ani, status: %{public}d.", status);
        return nullptr;
    }
    return intObj;
}

ani_object SecurityComponentAniMethod::CreateAniObject(ani_env* env, const char* descriptor)
{
    ani_class cls;
    ani_method ctor;
    ani_object newObject;
    env->FindClass(descriptor, &cls);
    CHECK_NULL_RETURN(cls, nullptr);
    env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor);
    CHECK_NULL_RETURN(ctor, nullptr);
    env->Object_New(cls, ctor, &newObject);
    return newObject;
}

ani_enum_item SecurityComponentAniMethod::ConvertSourceToolToAni(ani_env* env, SourceTool sourceTool)
{
    ani_enum sourceToolCls;
    env->FindEnum("arkui.component.common.SourceTool", &sourceToolCls);
    CHECK_NULL_RETURN(sourceToolCls, nullptr);
    ani_enum_item sourceToolEnum;
    std::string name;
    switch (sourceTool) {
        case SourceTool::UNKNOWN:
            name = "UNKNOWN";
            break;
        case SourceTool::FINGER:
            name = "FINGER";
            break;
        case SourceTool::PEN:
            name = "PEN";
            break;
        case SourceTool::MOUSE:
            name = "MOUSE";
            break;
        case SourceTool::TOUCHPAD:
            name = "TOUCHPAD";
            break;
        case SourceTool::JOYSTICK:
            name = "JOYSTICK";
            break;
        default:
            name = "UNKNOWN";
            break;
    }
    env->Enum_GetEnumItemByName(sourceToolCls, name.c_str(), &sourceToolEnum);
    return sourceToolEnum;
}

ani_enum_item SecurityComponentAniMethod::ConvertSourceTypeToAni(ani_env* env, SourceType source)
{
    ani_enum sourceTypeCls;
    env->FindEnum("arkui.component.common.SourceType", &sourceTypeCls);
    CHECK_NULL_RETURN(sourceTypeCls, nullptr);
    ani_enum_item sourceTypeEnum;
    std::string name;
    switch (source) {
        case SourceType::NONE:
            name = "UNKNOWN";
            break;
        case SourceType::MOUSE:
            name = "MOUSE";
            break;
        case SourceType::TOUCH:
            name = "TOUCH_SCREEN";
            break;
        case SourceType::KEYBOARD:
            name = "KEY";
            break;
        case SourceType::JOYSTICK:
            name = "JOYSTICK";
            break;
        default:
            name = "UNKNOWN";
            break;
    }
    env->Enum_GetEnumItemByName(sourceTypeCls, name.c_str(), &sourceTypeEnum);
    return sourceTypeEnum;
}

ani_object SecurityComponentAniMethod::CreateTarget(ani_env* env, const GestureEvent& info)
{
    const auto& localOffset = info.GetTarget().area.GetOffset();
    const auto& origin = info.GetTarget().origin;
    ani_object position = CreateAniObject(env, "arkui.hooks.SaveButtonOpsHandWritten.PositionImpl");
    CHECK_NULL_RETURN(position, nullptr);
    ani_object globalPosition = CreateAniObject(env, "arkui.hooks.SaveButtonOpsHandWritten.PositionImpl");
    CHECK_NULL_RETURN(globalPosition, nullptr);
    
    ani_object localx_obj = CreateDouble(env, localOffset.GetX().ConvertToVp());
    env->Object_SetPropertyByName_Ref(position, "x", localx_obj);
    ani_object localy_obj = CreateDouble(env, localOffset.GetY().ConvertToVp());
    env->Object_SetPropertyByName_Ref(position, "y", localy_obj);

    ani_object globalx_obj = CreateDouble(env, origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp());
    env->Object_SetPropertyByName_Ref(globalPosition, "x", globalx_obj);
    ani_object globaly_obj = CreateDouble(env, origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp());
    env->Object_SetPropertyByName_Ref(globalPosition, "y", globaly_obj);

    ani_object area = CreateAniObject(env, "arkui.hooks.SaveButtonOpsHandWritten.AreaImpl");
    CHECK_NULL_RETURN(area, nullptr);
    ani_object width_object = CreateDouble(env, info.GetTarget().area.GetWidth().ConvertToVp());
    env->Object_SetPropertyByName_Ref(area, "width", width_object);
    ani_object height_object = CreateDouble(env, info.GetTarget().area.GetHeight().ConvertToVp());
    env->Object_SetPropertyByName_Ref(area, "height", height_object);
    env->Object_SetPropertyByName_Ref(area, "position", position);
    env->Object_SetPropertyByName_Ref(area, "globalPosition", globalPosition);

    ani_object eventTarget = CreateAniObject(env, "arkui.hooks.SaveButtonOpsHandWritten.EventTargetImpl");
    CHECK_NULL_RETURN(eventTarget, nullptr);
    env->Object_SetPropertyByName_Ref(eventTarget, "area", area);
    if (!info.GetTarget().id.empty()) {
        ani_string idString {};
        env->String_NewUTF8(info.GetTarget().id.c_str(), info.GetTarget().id.size(), &idString);
        env->Object_SetPropertyByName_Ref(eventTarget, "id", idString);
    }
    return eventTarget;
}

ani_object SecurityComponentAniMethod::CreateClickEvent(ani_env* env, const GestureEvent& info)
{
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset globalDisplayOffset = info.GetGlobalDisplayLocation();
    
    ani_object clickInfoAni {};
    ani_class clickEventClass;
    env->FindClass("arkui.hooks.SaveButtonOpsHandWritten.ClickEventImpl", &clickEventClass);
    CHECK_NULL_RETURN(clickEventClass, nullptr);
    ani_method ctor;
    env->Class_FindMethod(clickEventClass, "<ctor>", ":", &ctor);
    CHECK_NULL_RETURN(ctor, nullptr);
    env->Object_New(clickEventClass, ctor, &clickInfoAni);
    CHECK_NULL_RETURN(clickInfoAni, nullptr);
    
    env->Object_SetPropertyByName_Double(clickInfoAni, "x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    env->Object_SetPropertyByName_Double(clickInfoAni, "y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    env->Object_SetPropertyByName_Long(clickInfoAni, "timestamp",
        (ani_long)(info.GetTimeStamp().time_since_epoch().count()));
    auto sourceType = ConvertSourceTypeToAni(env, info.GetSourceDevice());
    env->Object_SetPropertyByName_Ref(clickInfoAni, "source", sourceType);
    env->Object_SetPropertyByName_Double(clickInfoAni, "pressure", info.GetForce());
    env->Object_SetPropertyByName_Double(clickInfoAni, "tiltX", info.GetTiltX().value_or(0.0f));
    env->Object_SetPropertyByName_Double(clickInfoAni, "tiltY", info.GetTiltY().value_or(0.0f));
    auto sourceToolEnum = ConvertSourceToolToAni(env, info.GetSourceTool());
    env->Object_SetPropertyByName_Ref(clickInfoAni, "sourceTool", sourceToolEnum);
    auto target = CreateTarget(env, info);
    env->Object_SetPropertyByName_Ref(clickInfoAni, "target", target);
    ani_object targetDisplayId_obj = CreateInt32(env, info.GetTargetDisplayId());
    env->Object_SetPropertyByName_Ref(clickInfoAni, "targetDisplayId", targetDisplayId_obj);
    return clickInfoAni;
}
}
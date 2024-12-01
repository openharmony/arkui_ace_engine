/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#ifdef FORM_SUPPORTED
#include "core/components_ng/pattern/form/form_model_ng.h"
#endif
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
struct LiteralDimension {
    Dimension width;
    Dimension height;
};
namespace {
const auto FORM_DIMENSION_DIMENSION_1_2 = 1;
const auto FORM_DIMENSION_DIMENSION_2_2 = 2;
const auto FORM_DIMENSION_DIMENSION_2_4 = 3;
const auto FORM_DIMENSION_DIMENSION_4_4 = 4;
const auto FORM_DIMENSION_DIMENSION_2_1 = 5;
const auto FORM_DIMENSION_DIMENSION_1_1 = 6;
const auto FORM_DIMENSION_DIMENSION_6_4 = 7;
const auto FORM_COMPONENT_ID_KEY = "id";
const auto FORM_COMPONENT_ID_STRING_KEY = "idString";
const uint32_t FORM_COMPONENT_ID_INVALID = -1;
const std::string FORM_COMPONENT_ID_STRING_INVALID = "-1";
const uint32_t MIN_NUMBER_OF_ARK = 0;
const uint32_t MAX_NUMBER_OF_ARK = 0xFFFFFFFF;
// const int64_t MAX_NUMBER_OF_JS = 0x20000000000000;
} // namespace
namespace Converter {
template<>
LiteralDimension Convert(const Ark_Literal_Number_height_width& src)
{
    return LiteralDimension {
        .width = Converter::Convert<Dimension>(src.width),
        .height = Converter::Convert<Dimension>(src.height)
    };
}
template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FormDimension& src)
{
    switch (src) {
        case ARK_FORM_DIMENSION_DIMENSION_1_2: dst = FORM_DIMENSION_DIMENSION_1_2; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_2: dst = FORM_DIMENSION_DIMENSION_2_2; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_4: dst = FORM_DIMENSION_DIMENSION_2_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_4_4: dst = FORM_DIMENSION_DIMENSION_4_4; break;
        case ARK_FORM_DIMENSION_DIMENSION_2_1: dst = FORM_DIMENSION_DIMENSION_2_1; break;
        case ARK_FORM_DIMENSION_DIMENSION_1_1: dst = FORM_DIMENSION_DIMENSION_1_1; break;
        case ARK_FORM_DIMENSION_DIMENSION_6_4: dst = FORM_DIMENSION_DIMENSION_6_4; break;
        default: LOGE("Unexpected enum value in Ark_FormDimension: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<VisibleType>& dst, const Ark_Visibility& src)
{
    switch (src) {
        case ARK_VISIBILITY_VISIBLE: dst = VisibleType::VISIBLE; break;
        case ARK_VISIBILITY_HIDDEN: dst = VisibleType::INVISIBLE; break;
        case ARK_VISIBILITY_NONE: dst = VisibleType::GONE; break;
        default: LOGE("Unexpected enum value in Ark_Visibility: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace FormComponentInterfaceModifier {
void SetFormComponentOptionsImpl(Ark_NativePointer node,
                                 const Ark_FormInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA FormComponentInterfaceModifier::SetFormComponentOptionsImpl - CustomObject is not supported "
        "the type Ark_FormInfo::Opt_Want::Opt_Map_String_CustomObject::Ark_CustomObject.");
}
} // FormComponentInterfaceModifier
namespace FormComponentAttributeModifier {
void SizeImpl(Ark_NativePointer node,
              const Ark_Literal_Number_height_width* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto dimension = Converter::Convert<LiteralDimension>(*value);
    FormModelNG::SetSize(frameNode, dimension.width, dimension.height);
#endif // FORM_SUPPORTED
}
void ModuleNameImpl(Ark_NativePointer node,
                    const Ark_String* value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto name = Converter::Convert<std::string>(*value);
    FormModelNG::SetModuleName(frameNode, name);
#endif // FORM_SUPPORTED
}
void DimensionImpl(Ark_NativePointer node,
                   Ark_FormDimension value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::OptConvert<int32_t>(value);
    CHECK_NULL_VOID(opt);
    FormModelNG::SetDimension(frameNode, *opt);
#endif // FORM_SUPPORTED
}
void AllowUpdateImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    FormModelNG::AllowUpdate(frameNode, convValue);
#endif // FORM_SUPPORTED
}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{
#ifdef FORM_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::OptConvert<VisibleType>(value);
    CHECK_NULL_VOID(opt);
    FormModelNG::SetVisibility(frameNode, *opt);
#endif // FORM_SUPPORTED
}
void OnAcquiredImpl(Ark_NativePointer node,
                    const Callback_FormCallbackInfo_Void* value)
{


// #ifdef FORM_SUPPORTED
    
    
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);


    // test!!!
    std::printf("modifier: \n");
    // test!!!


    auto onAcquired = [arkCallback = CallbackHelper(*value)](const std::string& param) {
        uint32_t id = FORM_COMPONENT_ID_INVALID;
        std::string idString = FORM_COMPONENT_ID_STRING_INVALID;
        
        
        // test!!!
        std::printf("modifier: 2 %s\n", param.c_str());
        // test!!!
    

        auto sourceJson = JsonUtil::ParseJsonString(param);

        if (sourceJson && !sourceJson->IsNull()) {
            char *endptr;
            auto jsonId = sourceJson->GetString(FORM_COMPONENT_ID_KEY, FORM_COMPONENT_ID_STRING_INVALID);
            idString = sourceJson->GetString(FORM_COMPONENT_ID_STRING_KEY, FORM_COMPONENT_ID_STRING_INVALID);
            int64_t result = strtoul(jsonId.c_str(), &endptr, 10);
            
            
            // test!!!
            std::printf("modifier: 3 %s  result %ld max: %ld\n", param.c_str(), result, static_cast<int64_t>(MAX_NUMBER_OF_ARK));
            // test!!!

            // test!!!
            std::printf("modifier: 32 <> %d <>%d\n", (result >= MIN_NUMBER_OF_ARK && result <= MAX_NUMBER_OF_ARK), (*endptr == '\0' && result >= MIN_NUMBER_OF_ARK && result < MAX_NUMBER_OF_ARK));
            // test!!!


            if (*endptr == '\0' && result >= MIN_NUMBER_OF_ARK && result < MAX_NUMBER_OF_ARK) {
                 id = static_cast<uint32_t>(result);   
            }
            
           
            // test!!!
            std::printf("modifier: 33 %s  id: %d idString: %s\n", param.c_str(), id, idString.c_str());
            // test!!!
    
    
        }
        Ark_FormCallbackInfo parameter = {
            .id = Converter::ArkValue<Ark_Number>(id),
            .idString = Converter::ArkValue<Ark_String>(idString)
        };
    
    
        // test!!!
        std::printf("modifier: 4\n");
        // test!!!
    
    
        arkCallback.Invoke(parameter);
    
    
        // test!!!
        std::printf("modifier: 5\n");
        // test!!!
    
    
    };
    

    // test!!!
    std::printf("modifier: 6\n");
    // test!!!
    

    FormModelNG::SetOnAcquired(frameNode, std::move(onAcquired));
    
    
    // test!!!
     std::printf("modifier: 7\n");
    // test!!!
    


// //======================================
//     uint32_t = stoul()

// //======================================
//     auto sourceJson = JsonUtil::ParseJsonString(selectedStr);
//     auto id = sourceJson->GetValue(FORM_COMPONENT_ID_KEY);
//     auto month = sourceJson->GetValue(FORM_COMPONENT_ID_STRING_KEY);


//         auto year = DATE_MIN.GetYear();
//         auto month = DATE_MIN.GetMonth();
//         auto day = DATE_MIN.GetDay();
//         if (g_checkValidDateValues(sourceJson)) {
//             year = sourceJson->GetValue(YEAR)->GetInt();
//             month = sourceJson->GetValue(MONTH)->GetInt();
//             day = sourceJson->GetValue(DAY)->GetInt();

//     //===================================
//     auto host = GetHost();
//     CHECK_NULL_VOID(host);
//     auto eventHub = host->GetEventHub<FormEventHub>();
//     CHECK_NULL_VOID(eventHub);
//     int64_t onAcquireFormId = id < MAX_NUMBER_OF_JS ? id : -1;
//     auto json = JsonUtil::Create(true);
//     json->Put("id", std::to_string(onAcquireFormId).c_str());
//     json->Put("idString", std::to_string(id).c_str());
//     eventHub->FireOnAcquired(json->ToString());

//     //==================================
//     void FormModelNG::SetOnAcquired(std::function<void(const std::string&)>&& onAcquired)
// //==================================
//    auto frameNode = reinterpret_cast<FrameNode *>(node);
//     CHECK_NULL_VOID(frameNode);
//     CHECK_NULL_VOID(value);
//     auto onBreakpointChange = [arkCallback = CallbackHelper(*value)](const std::string& breakpoint) {
//         arkCallback.Invoke(Converter::ArkValue<Ark_String>(breakpoint));
//     };
//     GridRowModelNG::SetOnBreakPointChange(frameNode, std::move(onBreakpointChange));

//     void SetOnBreakPointChange(std::function<void(const std::string)>&& onChange) override;

// //====================================================

//     auto onChange = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* event) {
//         CHECK_NULL_VOID(event);
//         const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
//         CHECK_NULL_VOID(eventInfo);
//         auto selectedStr = eventInfo->GetSelectedStr();
//         auto sourceJson = JsonUtil::ParseJsonString(selectedStr);

//         auto year = DATE_MIN.GetYear();
//         auto month = DATE_MIN.GetMonth();
//         auto day = DATE_MIN.GetDay();
//         if (g_checkValidDateValues(sourceJson)) {
//             year = sourceJson->GetValue(YEAR)->GetInt();
//             month = sourceJson->GetValue(MONTH)->GetInt();
//             day = sourceJson->GetValue(DAY)->GetInt();
//         }
//         auto pickerDate = PickerDate(year, month, day);
//         auto result = Converter::ArkValue<Ark_Date>(pickerDate);
//         arkCallback.Invoke(result);
//     };
//     FormModelNG::SetOnAcquired(frameNode, std::move(onChange));
   
   
 
    

// #endif
}
void OnErrorImpl(Ark_NativePointer node,
                 const Callback_Literal_Number_errcode_String_msg_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnError(frameNode, convValue);
}
void OnRouterImpl(Ark_NativePointer node,
                  const Callback_Any_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA FormComponentInterfaceModifier::OnRouterImpl - CustomObject is not supported "
        "the type Callback_Any_Void includes Ark_CustomObject.");
}
void OnUninstallImpl(Ark_NativePointer node,
                     const Callback_FormCallbackInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnUninstall(frameNode, convValue);
}
void OnLoadImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FormComponentModelNG::SetOnLoad(frameNode, convValue);
}
} // FormComponentAttributeModifier
const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
{
    static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
        FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
        FormComponentAttributeModifier::SizeImpl,
        FormComponentAttributeModifier::ModuleNameImpl,
        FormComponentAttributeModifier::DimensionImpl,
        FormComponentAttributeModifier::AllowUpdateImpl,
        FormComponentAttributeModifier::VisibilityImpl,
        FormComponentAttributeModifier::OnAcquiredImpl,
        FormComponentAttributeModifier::OnErrorImpl,
        FormComponentAttributeModifier::OnRouterImpl,
        FormComponentAttributeModifier::OnUninstallImpl,
        FormComponentAttributeModifier::OnLoadImpl,
    };
    return &ArkUIFormComponentModifierImpl;
}

}

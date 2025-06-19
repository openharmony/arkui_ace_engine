/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/console_message_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr int MESSAGE_LEVEL_INFO = 2;
namespace ConsoleMessageAccessor {
void DestroyPeerImpl(Ark_ConsoleMessage peer)
{
    CHECK_NULL_VOID(peer);
    peer->webConsoleLog = nullptr;
    delete peer;
}
Ark_ConsoleMessage CtorImpl(const Ark_String* message,
                            const Ark_String* sourceId,
                            const Ark_Number* lineNumber,
                            Ark_MessageLevel messageLevel)
{
    CHECK_NULL_RETURN(message, nullptr);
    CHECK_NULL_RETURN(sourceId, nullptr);
    CHECK_NULL_RETURN(lineNumber, nullptr);
    auto level = EnumToInt(Converter::OptConvert<Converter::MessageLevel>(messageLevel));
    CHECK_NULL_RETURN(level, nullptr);
    return new ConsoleMessagePeer {
        .webConsoleLog = Referenced::MakeRefPtr<WebConsoleMessageParam>(
            Converter::Convert<std::string>(*message),
            Converter::Convert<std::string>(*sourceId),
            Converter::Convert<int>(*lineNumber),
            level.value()
        )
    };
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetMessageImpl(Ark_ConsoleMessage peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->webConsoleLog, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->webConsoleLog->GetLog();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_String GetSourceIdImpl(Ark_ConsoleMessage peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->webConsoleLog, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->webConsoleLog->GetSourceId();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_Number GetLineNumberImpl(Ark_ConsoleMessage peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->webConsoleLog, errValue);
    return Converter::ArkValue<Ark_Number>(peer->webConsoleLog->GetLineNumber());
}
Ark_MessageLevel GetMessageLevelImpl(Ark_ConsoleMessage peer)
{
    CHECK_NULL_RETURN(peer && peer->webConsoleLog, {});
    return Converter::ArkValue<Ark_MessageLevel>(
        static_cast<Converter::MessageLevel>(peer->webConsoleLog->GetLogLevel()));
}
} // ConsoleMessageAccessor
const GENERATED_ArkUIConsoleMessageAccessor* GetConsoleMessageAccessor()
{
    static const GENERATED_ArkUIConsoleMessageAccessor ConsoleMessageAccessorImpl {
        ConsoleMessageAccessor::DestroyPeerImpl,
        ConsoleMessageAccessor::CtorImpl,
        ConsoleMessageAccessor::GetFinalizerImpl,
        ConsoleMessageAccessor::GetMessageImpl,
        ConsoleMessageAccessor::GetSourceIdImpl,
        ConsoleMessageAccessor::GetLineNumberImpl,
        ConsoleMessageAccessor::GetMessageLevelImpl,
    };
    return &ConsoleMessageAccessorImpl;
}

struct ConsoleMessagePeer {
    virtual ~ConsoleMessagePeer() = default;
};
}

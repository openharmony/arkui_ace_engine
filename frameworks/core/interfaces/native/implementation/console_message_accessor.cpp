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
#include "core/interfaces/native/implementation/console_message_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr int MESSAGE_LEVEL_INFO = 2;
namespace ConsoleMessageAccessor {
ConsoleMessagePeer* CtorImpl(const Ark_String* message,
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
static void DestroyPeer(ConsoleMessagePeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->webConsoleLog = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(DestroyPeer);
}
void GetMessageImpl(ConsoleMessagePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->webConsoleLog);
    peer->webConsoleLog->GetLog();
    // log message need to be returned
    LOGE("ConsoleMessageAccessor::GetMessageImpl - return value need to be supported");
}
void GetSourceIdImpl(ConsoleMessagePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->webConsoleLog);
    peer->webConsoleLog->GetSourceId();
    // source id need to be returned
    LOGE("ConsoleMessageAccessor::GetSourceIdImpl - return value need to be supported");
}
Ark_Int32 GetLineNumberImpl(ConsoleMessagePeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->webConsoleLog, 0);
    return static_cast<Ark_Int32>(peer->webConsoleLog->GetLineNumber());
}
Ark_NativePointer GetMessageLevelImpl(ConsoleMessagePeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->webConsoleLog, 0);
    peer->webConsoleLog->GetLogLevel();
    // log level need to be returned
    LOGE("ConsoleMessageAccessor::GetMessageLevelImpl - return value need to be supported");
    return 0;
}
} // ConsoleMessageAccessor
const GENERATED_ArkUIConsoleMessageAccessor* GetConsoleMessageAccessor()
{
    static const GENERATED_ArkUIConsoleMessageAccessor ConsoleMessageAccessorImpl {
        ConsoleMessageAccessor::CtorImpl,
        ConsoleMessageAccessor::GetFinalizerImpl,
        ConsoleMessageAccessor::GetMessageImpl,
        ConsoleMessageAccessor::GetSourceIdImpl,
        ConsoleMessageAccessor::GetLineNumberImpl,
        ConsoleMessageAccessor::GetMessageLevelImpl,
    };
    return &ConsoleMessageAccessorImpl;
}

}

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

class %COMPONENT_ATTRIBUTE_NAME%StyleHolder {
    var value: ?((attributes: %COMPONENT_ATTRIBUTE_NAME%Interfaces) -> Unit)
    init (value: ?((attributes: %COMPONENT_ATTRIBUTE_NAME%Interfaces) -> Unit)) {
        this.value = value
    }
}

class %COMPONENT_ATTRIBUTE_NAME%ContentHolder {
    var value: ?(() -> Unit)
    init (value: ?(() -> Unit)) {
        this.value = value
    }
}


@Memo(
    public func Ark%COMPONENT_NAME%(
        style: ?((attributes: %COMPONENT_ATTRIBUTE_NAME%Interfaces) -> Unit),
        content_: ?(() -> Unit)%FUNCTION_PARAMETERS%
    ): Unit {
        let styleHolder = %COMPONENT_ATTRIBUTE_NAME%StyleHolder(style)
        let contentHolder = %COMPONENT_ATTRIBUTE_NAME%ContentHolder(content_)
        let receiver = remember({ =>
            %COMPONENT_CLASS_NAME%()
        })
        NodeAttach<%PEER_CLASS_NAME%>({ => %PEER_CLASS_NAME%.create(receiver, 0) }) {
            %PEER_CALLABLE_INVOKE%
            if (let Some(style) <- styleHolder.value) {
                style(receiver)
            }
            if (let Some(content_) <- contentHolder.value) {
                content_()
            }
        }
    }
)
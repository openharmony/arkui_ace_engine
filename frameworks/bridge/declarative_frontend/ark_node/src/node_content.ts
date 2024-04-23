/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

declare class ArkUINativeNodeContent {
    static getNativeContent(value: ArkUINativeNodeContent): Object;
}

class NodeContent extends Content {
    nativeContent_: ArkUINativeNodeContent;
    nativePtr_: Object;
    constructor() {
        super();
        this.nativeContent_ = new ArkUINativeNodeContent();
        this.nativePtr_ = ArkUINativeNodeContent.getNativeContent(this.nativeContent_);
    }
}
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

import image from '@ohos.multimedia.image';
import { BusinessError, AsyncCallback } from '@ohos.base';
import { CustomBuilder } from '@ohos.arkui.component';

export default namespace componentSnapshot {

    loadLibrary("componentSnapshot_ani");

    export interface SnapshotOptions {
        scale?: number
        waitUntilRenderFinished?: boolean
    }

    export native function createFromBuilder(builder: CustomBuilder, callback: AsyncCallback<image.PixelMap>,
        delay?: number, checkImageStatus?: boolean, options?: SnapshotOptions): void;
}

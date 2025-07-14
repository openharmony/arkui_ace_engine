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
import { KPointer , InteropNativeModule} from "@koalaui/interop"
import { CustomBuilder, SheetOptions, Bindable, BindSheetOps, ContentCoverOptions } from "../component"

export class BindSheetHandWritten {
    static hookSheetShowImpl(node: KPointer, value: Bindable<boolean>,  builder: CustomBuilder | undefined, options?: SheetOptions) {
        BindSheetOps.registerSheetShowCallback(node, value.value, (v) => {
            value.onChange(v)
        }, builder, options)
    }

    static hookBindContentCoverShowImpl(node: KPointer, value: Bindable<boolean>,  builder: CustomBuilder | undefined, options?: ContentCoverOptions) {
        BindSheetOps.registerBindContentCoverCallback(node, value.value, (v) => {
            value.onChange(v)
        }, builder, options)
    }
}
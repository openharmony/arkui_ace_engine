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

import { Callback } from '@ohos.base';

export default namespace mediaquery {
    loadLibrary("mediaquery_ani");
    export default interface MediaQueryResult {
        readonly matches: boolean;
        readonly media: string;
    }
    export interface MediaQueryListener {
        on(type: string, callback: Callback<MediaQueryResult>): void;
        off(type: string, callback?: Callback<MediaQueryResult>): void
    }
    class Mediaquery implements MediaQueryListener {
        private nativeSerializerResult:long = 0;
        constructor(serializerResult:long) {
            if(this.nativeSerializerResult == 0){
                this.nativeSerializerResult = serializerResult;
            }
        }
        public native on(type: string, callback: Callback<MediaQueryResult>): void;
        public native off(type: string, callback?: Callback<MediaQueryResult>): void
    }
    export native function matchMediaSync(condition: string): MediaQueryListener;
}
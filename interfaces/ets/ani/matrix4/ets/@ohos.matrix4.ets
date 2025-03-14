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

export default namespace matrix4 {
    loadLibrary("matrix4_ani");
    class Matrix4Result implements Matrix4Transit {
        private matrix4Object:long = 0;

        constructor(context:long) {
            if(this.matrix4Object == 0){
                this.matrix4Object = context;
            }
        }
    }
    
    export default interface Matrix4Transit {}

    export native function Matrix4_Identity():Matrix4Transit;

}
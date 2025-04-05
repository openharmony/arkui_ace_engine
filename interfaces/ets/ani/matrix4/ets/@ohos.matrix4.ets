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
    export interface TranslateOption {
        x?: number;
        y?: number;
        z?: number;
    }

    export interface ScaleOption {
        x?: number;
        y?: number;
        z?: number;
        centerX?: number;
        centerY?: number;
    }

    export interface RotateOption {
        x?: number;
        y?: number;
        z?: number;
        centerX?: number;
        centerY?: number;
        angle?: number;
    }

    export default interface Matrix4Transit {
        copy():Matrix4Transit;
        invert(): Matrix4Transit;
        combine(options: Matrix4Transit): Matrix4Transit;
        scale(options: ScaleOption): Matrix4Transit;
        rotate(options: RotateOption): Matrix4Transit;
        translate(options: TranslateOption): Matrix4Transit;
    }

    class Matrix4TransitInner implements Matrix4Transit {
        private matrix4Object:long = 0;

        constructor(context:long) {
            if(this.matrix4Object == 0){
                this.matrix4Object = context;
            }
        }
        public native copy():Matrix4Transit;
        public native invert():Matrix4Transit;
        public native combine(options: Matrix4Transit): Matrix4Transit;
        public native scale(options: ScaleOption): Matrix4Transit;
        public native rotate(options: RotateOption): Matrix4Transit;
        public native translate(options: TranslateOption): Matrix4Transit;
    }
    export native function identity():Matrix4Transit;
    export native function init(options: [
        number, number, number, number, 
        number, number, number, number,
        number, number, number, number,
        number, number, number, number]):Matrix4Transit;
}
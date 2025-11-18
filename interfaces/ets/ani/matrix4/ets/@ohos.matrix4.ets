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
        x?: double;
        y?: double;
        z?: double;
    }

    export interface ScaleOption {
        x?: double;
        y?: double;
        z?: double;
        centerX?: double;
        centerY?: double;
    }

    export interface RotateOption {
        x?: double;
        y?: double;
        z?: double;
        centerX?: double;
        centerY?: double;
        angle?: double;
    }

    export interface Point {
        x: double;
        y: double;
    }

    export interface PolyToPolyOptions {
        src: Array<Point>;
        srcIndex?: int;
        dst: Array<Point>;
        dstIndex?: int;
        pointCount?: int;
    }

    export default interface Matrix4Transit {
        copy():Matrix4Transit;
        invert(): Matrix4Transit;
        combine(options: Matrix4Transit): Matrix4Transit;
        scale(options: ScaleOption): Matrix4Transit;
        rotate(options: RotateOption): Matrix4Transit;
        translate(options: TranslateOption): Matrix4Transit;
        skew(x: double, y: double): Matrix4Transit;
        setPolyToPoly(options: PolyToPolyOptions): Matrix4Transit;
        transformPoint(options: [
            double,
            double
        ]): [
            double,
            double
        ];
    }

    class Matrix4TransitInner implements Matrix4Transit {
        private matrix4Object: long = 0;

        static {
            loadLibrary("matrix4_ani");
        }

        constructor(context: long) {
            this.matrix4Object = context;
        }

        static matrixTransferStatic(input: Any): Any {
            let inputVal = ESValue.wrap(input) as ESValue;
            if (inputVal && inputVal.getProperty("matrix4x4")) {
                let matrixTuple = inputVal.getProperty("matrix4x4");
                let arrVal: number[] = new Array<number>
                for (let i = 0; i < 16; i++) {
                    arrVal.push(matrixTuple.getProperty(i).toNumber());
                }
                return Matrix4TransitInner.nativeTransferStatic(arrVal);
            }
            return undefined;
        }

        static matrixTransferDynamic(input: Any): Any {
            let matrixObj = input as Matrix4TransitInner;
            if (matrixObj) {
                let addr = matrixObj.matrix4Object;
                let module = ESValue.load("@ohos.matrix4");
                let initFunc = module.getProperty("__InitTransfer__")
                if (initFunc) {
                    let initArr = initFunc.invoke(ESObject.wrap(addr));
                    return initArr;
                }
            }
            return undefined;
        }

        private static native nativeTransferStatic(input: Any): Any;

        public native copy():Matrix4Transit;
        public native invert():Matrix4Transit;
        public native combine(options: Matrix4Transit): Matrix4Transit;
        public native scale(options: ScaleOption): Matrix4Transit;
        public native rotate(options: RotateOption): Matrix4Transit;
        public native translate(options: TranslateOption): Matrix4Transit;
        public native skew(x: double, y: double): Matrix4Transit;
        public native setPolyToPoly(options: PolyToPolyOptions): Matrix4Transit;
        public native transformPoint(options: [
                            double,
                            double
                        ]): [
                            double,
                            double
                        ]; 
    }
    export native function identity():Matrix4Transit;
    export native function init(options: [
        double, double, double, double, 
        double, double, double, double,
        double, double, double, double,
        double, double, double, double]):Matrix4Transit;
}
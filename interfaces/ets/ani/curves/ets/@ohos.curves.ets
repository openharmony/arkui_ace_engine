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
export default namespace curves {
    loadLibrary("curves_ani");
    export enum Curve
    {
        Linear = 0,
        Ease = 1,
        EaseIn = 2,
        EaseOut = 3,
        EaseInOut = 4,
        FastOutSlowIn = 5,
        LinearOutSlowIn = 6,
        FastOutLinearIn = 7,
        ExtremeDeceleration = 8,
        Sharp = 9,
        Rhythm = 10,
        Smooth = 11,
        Friction = 12,
    };

    export native function cubicBezierCurve(x1: number, y1: number, x2: number, y2: number):ICurve;
    export native function cubicBezier(x1: number, y1: number, x2: number, y2: number):string;
    export native function springMotion(response?: number, dampingFraction?: number, overlapDuration?: number): ICurve;
    export native function initCurve(curve?: Curve):ICurve;
    export native function interpolatingSpring(velocity: number, mass: number, stiffness: number, damping: number):ICurve;
    export native function springCurve(velocity: number, mass: number, stiffness: number, damping: number):ICurve;
    export native function responsiveSpringMotion(response?: number, dampingFraction?: number, overlapDuration?: number): ICurve;

    export interface ICurve
    {
        interpolate(fraction: number) : number;
    }
    class Curves implements ICurve
    {
        private  nativeContext:long = 0;
    
        constructor(context:long) {
            if(this.nativeContext == 0){
                this.nativeContext = context;
            }
        }
        public native interpolate(fraction: number): number;
    }
}
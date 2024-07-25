/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

const __patternlock__ = requireInternal('arkui.patternlock');

class PatternLock extends JSViewAbstract {
    static create(value) {
        __patternlock__.create(value);
    }

    static sideLength(value) {
        __patternlock__.sideLength(value);
    }

    static circleRadius(value) {
        __patternlock__.circleRadius(value);
    }

    static pathStrokeWidth(value) {
        __patternlock__.pathStrokeWidth(value);
    }

    static activeColor(value) {
        __patternlock__.activeColor(value);
    }

    static selectedColor(value) {
        __patternlock__.selectedColor(value);
    }

    static pathColor(value) {
        __patternlock__.pathColor(value);
    }

    static regularColor(value) {
        __patternlock__.regularColor(value);
    }

    static autoReset(value) {
        __patternlock__.autoReset(value);
    }

    static onPatternComplete(value) {
        __patternlock__.onPatternComplete(value);
    }
}

export default PatternLock;


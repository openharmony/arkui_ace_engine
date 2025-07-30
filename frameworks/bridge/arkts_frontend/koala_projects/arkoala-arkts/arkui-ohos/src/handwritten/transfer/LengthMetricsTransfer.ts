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

import { LengthMetrics, LengthUnit } from "../../Graphics"
import { int32 } from "@koalaui/common"

export class LengthMetricsTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            throw Error("The LengthMetrics is not object convert fail.");
        }
        const value = ESValue.wrap(input).getProperty("value").toNumber();
        const unit = ESValue.wrap(input).getProperty("unit").toNumber();
        let unitInt32 = unit as int32;
        let lengthUnit: LengthUnit = LengthUnit.VP;
        if (unitInt32 >= LengthUnit.PX || unitInt32 <= LengthUnit.LPX) {
            lengthUnit = unitInt32 as LengthUnit;
        }
        let sizeInternal = new LengthMetrics(value, lengthUnit);
        return sizeInternal;
    }
    static transferDynamic(input: Object): Any {
        if (input == null) {
            throw Error("The LengthMetrics is null, convert fail.");
        }
        if (input == undefined) {
            throw Error("The LengthMetrics is undefined, convert fail.");
        }
        let staticValue = input as LengthMetrics;
        if (staticValue == null) {
            throw Error("Not a LengthMetrics object, convert fail.");
        }
        if (staticValue == undefined) {
            throw Error("Not a LengthMetrics object, convert fail.");
        }
        let nodeModule = ESValue.load("@ohos.arkui.node");
        let lengthMetricsModule = nodeModule.getProperty("LengthMetrics");
        let dynamicValue = lengthMetricsModule.instantiate();
        dynamicValue.setProperty('unit', ESValue.wrap(staticValue.unit.valueOf()));
        dynamicValue.setProperty('value', ESValue.wrap(staticValue.value));
        return dynamicValue.unwrap();
    }
}
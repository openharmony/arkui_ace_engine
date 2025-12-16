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

import { ColorMetrics } from '../../Graphics'
import { int32 } from "@koalaui/common"

const MAX_CHANNEL_VALUE = 0xFF;

export class ColorMetricsTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            throw Error('The ColorMetrics is not object convert fail.');
        }
        let resourceId: number = -1;
        const red = ESValue.wrap(input).getProperty('red_').toNumber();
        const green = ESValue.wrap(input).getProperty('green_').toNumber();
        const blue = ESValue.wrap(input).getProperty('blue_').toNumber();
        const alpha = ESValue.wrap(input).getProperty('alpha_').toNumber()/MAX_CHANNEL_VALUE;
        if (ESValue.wrap(input).hasProperty('resourceId_')) {
            resourceId = ESValue.wrap(input).getProperty('resourceId_').toNumber();
        }
        let colorMetrics = ColorMetrics.rgba(red, green, blue, alpha);
        colorMetrics.setResourceId(resourceId as int32);
        return colorMetrics;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            throw Error('The ColorMetrics is null, convert fail.');
        }
        if (input === undefined) {
            throw Error('The ColorMetrics is undefined, convert fail.');
        }
        let staticValue = input as ColorMetrics
        if (staticValue === null) {
            throw Error('Not a ColorMetrics object, convert fail.');
        }
        if (staticValue === undefined) {
            throw Error('Not a ColorMetrics object, convert fail.');
        }
        let nodeModule = ESValue.load('@ohos.arkui.node');
        let ColorMetricsModule = nodeModule.getProperty('ColorMetrics')
        let ret = ColorMetricsModule.invokeMethod('rgba', staticValue.red, staticValue.green ,staticValue.blue, staticValue.alpha/MAX_CHANNEL_VALUE);
        let resId = staticValue.getResourceId();
        if (resId !== undefined) {
            ret.setProperty('resourceId_', ESValue.wrap(resId));
        }
        return ret.unwrap();
    }
}

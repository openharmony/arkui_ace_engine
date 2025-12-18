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


import { ArkUIAniModule } from 'arkui.ani'
import { ColorFilter } from '../component/units'
import { MaterializedBaseTag } from '@koalaui/interop'

export class ColorFilterTransfer {
    static transferStatic(input: Any): Any {
        if (typeof (input) !== 'object' || input === null) {
            return undefined;
        }
        let esValue: ESValue = input as ESValue;
        const global = ESValue.getGlobal();
        const getColorFilterPointerFunc = global.getProperty('GetColorFilterPointer');
        if (getColorFilterPointerFunc.isNull() || getColorFilterPointerFunc.isUndefined()) {
            return undefined;
        }
        const pointer = getColorFilterPointerFunc.invoke(esValue);
        if (!pointer.isNumber()) {
            return undefined;
        }
        let pointerVal = pointer.toNumber() as long;
        let ctorPtr = ArkUIAniModule._Image_ColorFilter_TransferStatic(pointerVal);
        if (ctorPtr === 0) {
            return undefined;
        }
        let colorFilter = new ColorFilter(MaterializedBaseTag.NOP, ctorPtr);
        return colorFilter;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            return undefined;
        }
        if (!(input instanceof ColorFilter)) {
            return undefined;
        }
        let colorFilter = input as ColorFilter;
        let colorFilterObj = ESValue.instantiateEmptyObject();
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('WrapColorFilterPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return undefined;
        }
        let peerPtr = colorFilter?.peer?.ptr;
        if (peerPtr === undefined) {
            return undefined;
        }
        let pointer = ArkUIAniModule._Image_ColorFilter_TransferDynamic(peerPtr);
        if (pointer === 0) {
            return undefined;
        }
        wrapFunc.invoke(colorFilterObj, ESObject.wrap(pointer));
        return colorFilterObj;
    }
}

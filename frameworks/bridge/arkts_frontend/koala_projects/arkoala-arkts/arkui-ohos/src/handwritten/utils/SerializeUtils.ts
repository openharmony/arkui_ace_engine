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

import { ResourceColor, Color } from 'arkui/component';
import { int32 } from "@koalaui/common"
import { runtimeType, RuntimeType } from '@koalaui/interop';
import { Serializer } from 'arkui/component';
import { TypeChecker } from '#components';
import { Resource } from 'global.resource';

export class SerializeUtils {
    static writeColorArray(thisSerializer: Serializer, colorArray: ResourceColor[]) {
        thisSerializer.writeInt32(colorArray.length as int32);
        for (let i = 0; i < colorArray.length; i++) {
            let color_type: int32 = runtimeType(colorArray[i]);
            if (TypeChecker.isColor(colorArray[i])) {
                thisSerializer.writeInt8(0 as int32);
                const color_0 = colorArray[i] as Color;
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0));
            } else if (RuntimeType.NUMBER == color_type) {
                thisSerializer.writeInt8(1 as int32);
                const color_1 = colorArray[i] as number;
                thisSerializer.writeNumber(color_1);
            } else if (RuntimeType.STRING == color_type) {
                thisSerializer.writeInt8(2 as int32);
                const color_2 = colorArray[i] as string;
                thisSerializer.writeString(color_2);
            } else if (RuntimeType.OBJECT == color_type) {
                thisSerializer.writeInt8(3 as int32);
                const color_3 = colorArray[i] as Resource;
                thisSerializer.writeResource(color_3);
            }
        }
    }
}

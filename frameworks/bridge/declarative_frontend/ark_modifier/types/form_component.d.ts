/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
declare enum FormDimension {
    Dimension_1_2 = 0,
    Dimension_2_2 = 1,
    Dimension_2_4 = 2,
    Dimension_4_4 = 3,
    Dimension_2_1 = 4,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
    DIMENSION_2_3 = 8,
    DIMENSION_3_3 = 9
}
declare enum FormRenderingMode {
    FULL_COLOR = 0,
    SINGLE_COLOR = 1
}
declare enum FormShape {
    RECT = 1,
    CIRCLE = 2
}
enum FormColorMode {
    MODE_AUTO = -1,
    MODE_DARK = 0,
    MODE_LIGHT = 1
}
declare interface FormInfo {
    id: number | string;
    name: string;
    bundle: string;
    ability: string;
    module: string;
    dimension?: FormDimension;
    temporary?: boolean;
    want?: import('../api/@ohos.app.ability.Want').default;
    renderingMode?: FormRenderingMode;
    shape?: FormShape;
    exemptAppLock?: boolean;
}
interface FormComponentInterface {
    (value: FormInfo): FormComponentAttribute;
}
interface FormCallbackInfo {
    id: number;
    idString: string;
    isLocked: boolean;
}
interface FormSize {
    width: number;
    height: number;
}
interface ErrorInformation {
    errcode: number;
    msg: string;
}
declare class FormComponentAttribute extends CommonMethod<FormComponentAttribute> {
}
declare const FormComponent: FormComponentInterface;
declare const FormComponentInstance: FormComponentAttribute;

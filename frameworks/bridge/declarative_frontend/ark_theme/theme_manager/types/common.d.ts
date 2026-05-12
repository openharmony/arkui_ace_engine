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

// interface_sdk-js/api/@internal/component/ets/units.d.ts
declare type ResourceColor = Color | number | string | Resource;

type FontWeight = 'lighter' | 'normal' | 'regular' | 'medium' | 'bold' | 'bolder' | number;

// interface_sdk-js/api/@internal/component/ets/common.d.ts
declare interface Resource {
  bundleName: string;
  moduleName: string;
  id: number;
  params?: Array<string | number | Resource>;
  type?: number;
}

// interface_sdk-js/api/@internal/component/ets/common.d.ts
declare enum Color {
  White = 0,
  Black = 1,
  Blue = 2,
  Brown = 3,
  Gray = 4,
  Green = 5,
  Grey = 6,
  Orange = 7,
  Pink = 8,
  Red = 9,
  Yellow = 10,
  Transparent = 11
}
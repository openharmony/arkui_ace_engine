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
 
 export const backgroundColorTestList: (ResourceColor|undefined)[] = [
  //1 不设置
  ,
  //2 str-16进制
  '#BBB2C8',
  //3 str非法值
  'rgba(red, green, blue, op)',
  //4 Color枚举
  Color.Orange,
  //5 rgba
  'rgba(182, 197, 209, 100)',
  //6 num
  0xA6C2BE,
  //7 undefined
  undefined,
  //8 res
  $r('app.color.Color_pink'),
  //9 res异常值
  $r('app.string.MainAbility_label'),
  //10 Color透明色
  Color.Transparent,
  //11
  '#ffc9eeea'
]
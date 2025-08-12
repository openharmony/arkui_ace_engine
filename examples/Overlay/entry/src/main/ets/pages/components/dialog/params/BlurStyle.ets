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
 
 export const blurStyleTestList: (BlurStyle|undefined)[] = [
  //1
  ,
  //2
  BlurStyle.Thin,
  //3
  undefined,
  //4
  BlurStyle.Regular,
  //5
  BlurStyle.Thick,
  //6
  1237,  //验证枚举类型异常值
  //7
  BlurStyle.BACKGROUND_THIN,
  //8
  BlurStyle.BACKGROUND_REGULAR,
  //9
  BlurStyle.BACKGROUND_THICK,
  //10
  BlurStyle.BACKGROUND_ULTRA_THICK,
  //11
  BlurStyle.NONE,
  //12
  BlurStyle.COMPONENT_ULTRA_THIN,
  //13
  BlurStyle.COMPONENT_THIN,
  //14
  BlurStyle.COMPONENT_REGULAR,
  //15
  BlurStyle.COMPONENT_THICK,
  //16
  BlurStyle.COMPONENT_ULTRA_THICK,
]
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

export class Constants {
  static readonly TEXT_FONT_SIZE = 20
  static readonly MARGIN_TOP = 20
  static readonly WIDTH_SIZE = '70%'
  static readonly HEIGHT_SIZE = '7%'
  static readonly LANGUAGE = new Map<string, string>()
    .set("ar-EG", "阿拉伯语").set("zh-Hans", "汉语")

  static getCaseName(name: string, num: number) {
    return name + String("0".repeat(2) + num).slice(-2) + '00';
  }
}
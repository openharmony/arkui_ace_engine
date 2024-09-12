/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function textClockFontFeatureTest() {
  /*
  * TextClock组件 FontFeature属性
  * 找到画面id为textClockFontFeature的TextClock组件
  * 获取textClock的FontFeature属性与期待值'normal'比对
  */
  defineTest('textClockFontFeatureTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFontFeatureTest running')
    let driver: Tester = Tester.create()
    let textClock: Component = await driver.findComponent(Matcher.create().id('textClockFontFeature').enabled(true))
    let fontFeature: string = await textClock.getInspectorInfo()
    assertFalse(JSON.parse(fontFeature).$attrs.fontFeature.value == undefined)
    assertEqual(JSON.parse(fontFeature).$attrs.fontFeature, 'normal')
  }, 0)
}
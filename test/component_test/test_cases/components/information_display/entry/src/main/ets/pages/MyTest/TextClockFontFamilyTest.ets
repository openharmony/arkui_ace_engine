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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function textClockFontFamilyTest() {
  /*
  * TextClock组件 FontFamily属性
  * 找到画面id为textClockFontFamily的TextClock组件
  * 找到画面文本为TextClockFontFamily的Button组件
  * 获取textClock的FontFamily属性与期待值'Arial'比对
  * 点击button，变更textClock的FontFamily属性值为'TESTRawFile'
  * 获取textClock的FontFamily属性与期待值'TESTRawFile'比对
  */
  defineTest('textClockFontFamilyTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFontFamilyTest running')
    let driver: Tester = Tester.create()
    let textClock: Component = await driver.findComponent(Matcher.create().id('textClockFontFamily').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextClockFontFamily').enabled(true))
    let fontFamily1: string = await textClock.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily1).$attrs.fontFamily, 'Arial')
    await button.tap()
    let fontFamily2: string = await textClock.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily2).$attrs.fontFamily, 'TESTRawFile')
  }, 0)
}
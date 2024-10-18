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

export default async function buttonFontFamilyTest() {
  /*
   * Button组件 FontFamily属性
   * 找到画面id为buttonFontFamily的Button组件
   * 找到画面文本为ButtonFontFamily的Button组件
   * 获取buttonFontFamily的FontFamily属性与期待值'Arial'比对
   * 点击button，变更buttonFontFamily的FontFamily属性值为'TESTFONT'
   * 获取buttonFontFamily的FontFamily属性与期待值'TESTFONT'比对
   */
  defineTest('buttonFontFamilyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonFontFamilyTestDemo running')
    let driver: Tester = Tester.create()
    let buttonFontFamily: Component = await driver.findComponent(Matcher.create().id('buttonFontFamily').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFontFamily').enabled(true))

    let fontFamily1: string = await buttonFontFamily.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily1).$attrs.fontFamily, 'Arial')

    await button.tap()
    let fontFamily2: string = await buttonFontFamily.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily2).$attrs.fontFamily, 'TESTFONT')
  }, 0)
}
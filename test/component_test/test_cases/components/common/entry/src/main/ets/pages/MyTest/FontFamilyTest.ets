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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function fontFamilyTest() {
  /*
   * Text组件 FontFamily通用属性
   * 找到画面id为textFontFamily的组件
   * 找到画面text为ButtonFontFamily的button组件
   * 获取textFontFamily的FontFamily属性与期待值 'Arial' 比较
   * 点击button，变更textFontFamily的FontFamily属性为 'font'
   * 获取textFontFamily的FontFamily属性与期待值 'font' 比较
   */
  defineTest('fontFamilyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('fontFamilyTestDemo running')
    let driver: Tester = Tester.create()
    let textFontFamily: Component = await driver.findComponent(Matcher.create().id('textFontFamily').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFontFamily').enabled(true))
    let fontFamily1: string = await textFontFamily.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily1).$attrs.fontFamily, 'Arial')

    await button.tap()
    let fontFamily2: string = await textFontFamily.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily2).$attrs.fontFamily, 'font')
  }, 0)
}
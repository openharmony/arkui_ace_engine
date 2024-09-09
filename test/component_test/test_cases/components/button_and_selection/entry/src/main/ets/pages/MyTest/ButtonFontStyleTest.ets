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

export default async function buttonFontStyleTest() {
  /*
   * Button组件 FontStyle属性
   * 找到画面id为buttonFontStyle的Button组件
   * 找到画面文本为ButtonFontStyle的Button组件
   * 获取buttonFontStyle的FontStyle属性与期待值FontStyle.Normal比对
   * 点击button，变更buttonFontStyle的FontStyle属性值为FontStyle.Italic
   * 获取buttonFontStyle的FontStyle属性与期待值FontStyle.Italic比对
   */
  defineTest('buttonFontStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonFontStyleTestDemo running')
    let driver: Tester = Tester.create()
    let buttonFontStyle: Component = await driver.findComponent(Matcher.create().id('buttonFontStyle').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFontStyle').enabled(true))

    let fontStyle1: string = await buttonFontStyle.getInspectorInfo()
    assertEqual(JSON.parse(fontStyle1).$attrs.fontStyle, 'FontStyle.Normal')

    await button.tap()
    let fontStyle2: string = await buttonFontStyle.getInspectorInfo()
    assertEqual(JSON.parse(fontStyle2).$attrs.fontStyle, 'FontStyle.Italic')
  }, 0)
}
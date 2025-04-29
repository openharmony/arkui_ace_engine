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

export default async function buttonButtonStyleTest() {
  /*
   * Button组件 ButtonStyle属性
   * 找到画面id为buttonButtonStyle1，buttonButtonStyle2的Button组件
   * 找到画面文本为ButtonButtonStyle2的Button组件
   * 获取buttonButtonStyle1的ButtonStyle属性与期待值ButtonStyleMode.EMPHASIZED比对
   * 获取buttonButtonStyle2的ButtonStyle属性与期待值ButtonStyleMode.NORMAL比对
   * 点击button，变更buttonButtonStyle2的ButtonStyle属性值为ButtonStyleMode.TEXTUAL
   * 获取buttonButtonStyle2的ButtonStyle属性与期待值ButtonStyleMode.TEXTUAL比对
   */
  defineTest('buttonButtonStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonButtonStyleTestDemo running')
    let driver: Tester = Tester.create()
    let buttonButtonStyle1: Component =
      await driver.findComponent(Matcher.create().id('buttonButtonStyle1').enabled(true))
    let buttonButtonStyle2: Component =
      await driver.findComponent(Matcher.create().id('buttonButtonStyle2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonButtonStyle2').enabled(true))

    let buttonStyle1: string = await buttonButtonStyle1.getInspectorInfo()
    assertEqual(JSON.parse(buttonStyle1).$attrs.buttonStyle, 'ButtonStyleMode.EMPHASIZED')

    let buttonStyle2: string = await buttonButtonStyle2.getInspectorInfo()
    assertEqual(JSON.parse(buttonStyle2).$attrs.buttonStyle, 'ButtonStyleMode.NORMAL')

    await button.tap()
    let buttonStyle3: string = await buttonButtonStyle2.getInspectorInfo()
    assertEqual(JSON.parse(buttonStyle3).$attrs.buttonStyle, 'ButtonStyleMode.TEXTUAL')
  }, 0)
}
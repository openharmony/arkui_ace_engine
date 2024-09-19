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

export default async function buttonControlSizeTest() {
  /*
   * Button组件 ControlSize属性
   * 找到画面id为buttonControlSize的Button组件
   * 找到画面文本为ButtonControlSize的Button组件
   * 获取buttonControlSize的ControlSize属性与期待值ControlSize.SMALL比对
   * 点击button，变更buttonControlSize的ControlSize属性值为ControlSize.NORMAL
   * 获取buttonControlSize的ControlSize属性与期待值ControlSize.NORMAL比对
   */
  defineTest('buttonControlSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonControlSizeTestDemo running')
    let driver: Tester = Tester.create()
    let buttonControlSize: Component =
      await driver.findComponent(Matcher.create().id('buttonControlSize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonControlSize').enabled(true))

    let controlSize1: string = await buttonControlSize.getInspectorInfo()
    assertEqual(JSON.parse(controlSize1).$attrs.controlSize, 'ControlSize.SMALL')

    await button.tap()
    let controlSize2: string = await buttonControlSize.getInspectorInfo()
    assertEqual(JSON.parse(controlSize2).$attrs.controlSize, 'ControlSize.NORMAL')
  }, 0)
}
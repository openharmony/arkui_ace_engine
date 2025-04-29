/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function selectMenuAlignTest() {
  /*
  * Select组件 MenuAlign属性
  * 找到画面id为selectMenuAlign1,selectMenuAlign2的Select组件
  * 找到画面文本为SelectMenuAlign的Button组件
  * 获取selectMenuAlign1的MenuAlign属性与期待值{ 'MenuAlignType.Start',{dx: 0, dy: 0} }比对
  * 获取selectMenuAlign2的MenuAlign属性与期待值{ 'MenuAlignType.Center',{dx: 10, dy: 10} }比对
  * 点击button，变更selectMenuAlign2的MenuAlign属性值为{ 'MenuAlignType.End',{dx: -5, dy: -5} }
  * 获取selectMenuAlign2的MenuAlign属性与期待值{ 'MenuAlignType.End',{dx: -5, dy: -5} }比对
  */
  defineTest('selectMenuAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectMenuAlignTestDemo running')
    let driver: Tester = Tester.create()
    let selectMenuAlign1: Component = await driver.findComponent(Matcher.create().id('selectMenuAlign1').enabled(true))
    let selectMenuAlign2: Component = await driver.findComponent(Matcher.create().id('selectMenuAlign2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectMenuAlign').enabled(true))

    let menuAlign1: string = await selectMenuAlign1.getInspectorInfo()
    assertEqual(JSON.parse(menuAlign1).$attrs.menuAlign.alignType, 'MenuAlignType.Start')
    assertEqual(JSON.parse(menuAlign1)
      .$attrs
      .menuAlign
      .offset
      .dX, 0)
    assertEqual(JSON.parse(menuAlign1)
      .$attrs
      .menuAlign
      .offset
      .dY, 0)

    let menuAlign2: string = await selectMenuAlign2.getInspectorInfo()
    assertEqual(JSON.parse(menuAlign2).$attrs.menuAlign.alignType, 'MenuAlignType.Center')
    assertEqual(JSON.parse(menuAlign2)
      .$attrs
      .menuAlign
      .offset
      .dX, 10)
    assertEqual(JSON.parse(menuAlign2)
      .$attrs
      .menuAlign
      .offset
      .dY, 10)

    await button.tap()
    let menuAlign3: string = await selectMenuAlign2.getInspectorInfo()
    assertEqual(JSON.parse(menuAlign3).$attrs.menuAlign.alignType, 'MenuAlignType.End')
    assertEqual(JSON.parse(menuAlign3)
      .$attrs
      .menuAlign
      .offset
      .dX, -5)
    assertEqual(JSON.parse(menuAlign3)
      .$attrs
      .menuAlign
      .offset
      .dY, -5)
  }, 0)
}
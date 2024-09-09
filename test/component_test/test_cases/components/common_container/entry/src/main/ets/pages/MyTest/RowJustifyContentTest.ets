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

export default async function rowJustifyContentTest() {
  /*
   * Row组件 JustifyContent属性
   * 找到id为rowJustifyContent1，rowJustifyContent2，rowJustifyContent3，rowJustifyContent4，rowJustifyContent5的Row组件
   * 找到画面文本为RowJustifyContent的Button组件
   * 获取row1的JustifyContent属性与期待值FlexAlign.Start比对
   * 获取row2的JustifyContent属性与期待值FlexAlign.Center比对
   * 获取row3的JustifyContent属性与期待值FlexAlign.End比对
   * 获取row4的JustifyContent属性与期待值FlexAlign.SpaceBetween比对
   * 获取row5的JustifyContent属性与期待值FlexAlign.SpaceAround比对
   * 点击button，变更row5的AlignItems属性值为FlexAlign.SpaceEvenly
   * 获取row5的JustifyContent属性与期待值FlexAlign.SpaceEvenly比对
   */
  defineTest('rowJustifyContentTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('rowJustifyContentTestDemo running')
    let driver: Tester = Tester.create()
    let rowJustifyContent1: Component = await driver.findComponent(Matcher.create()
      .id('rowJustifyContent1')
      .enabled(true))
    let rowJustifyContent2: Component = await driver.findComponent(Matcher.create()
      .id('rowJustifyContent2')
      .enabled(true))
    let rowJustifyContent3: Component = await driver.findComponent(Matcher.create()
      .id('rowJustifyContent3')
      .enabled(true))
    let rowJustifyContent4: Component = await driver.findComponent(Matcher.create()
      .id('rowJustifyContent4')
      .enabled(true))
    let rowJustifyContent5: Component = await driver.findComponent(Matcher.create()
      .id('rowJustifyContent5')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create().text('RowJustifyContent').enabled(true)))

    let justifyContent1: string = await rowJustifyContent1.getInspectorInfo()
    assertEqual(JSON.parse(justifyContent1).$attrs.justifyContent, 'FlexAlign.Start')

    let justifyContent2: string = await rowJustifyContent2.getInspectorInfo()
    assertEqual(JSON.parse(justifyContent2).$attrs.justifyContent, 'FlexAlign.Center')

    let justifyContent3: string = await rowJustifyContent3.getInspectorInfo()
    assertEqual(JSON.parse(justifyContent3).$attrs.justifyContent, 'FlexAlign.End')

    let justifyContent4: string = await rowJustifyContent4.getInspectorInfo()
    assertEqual(JSON.parse(justifyContent4).$attrs.justifyContent, 'FlexAlign.SpaceBetween')

    let justifyContent5: string = await rowJustifyContent5.getInspectorInfo()
    assertEqual(JSON.parse(justifyContent5).$attrs.justifyContent, 'FlexAlign.SpaceAround')
    await button.tap()
    let justifyContent6: string = await rowJustifyContent5.getInspectorInfo()
    assertEqual(JSON.parse(justifyContent6).$attrs.justifyContent, 'FlexAlign.SpaceEvenly')
  }, 0)
}
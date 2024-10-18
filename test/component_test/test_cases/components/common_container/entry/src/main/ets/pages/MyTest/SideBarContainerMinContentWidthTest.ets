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

export default async function sideBarContainerMinContentWidthTest() {
  /*
   * SideBarContainer组件 MinContentWidth属性
   * 找到id为sideBarContainerMinContentWidth1，sideBarContainerMinContentWidth2，sideBarContainerMinContentWidth3，sideBarContainerMinContentWidth4，sideBarContainerMinContentWidth5，sideBarContainerMinContentWidth6，sideBarContainerMinContentWidth7，sideBarContainerMinContentWidth8的SideBarContainer组件
   * 找到画面文本为SideBarContainerSideBarWidth的Button组件
   * 获取sideBarContainer1的MinContentWidth属性与期待值'360vp'比对
   * 获取sideBarContainer2的MinContentWidth属性与期待值'0vp'比对
   * 获取sideBarContainer3的MinContentWidth属性与期待值'370vp'比对
   * 获取sideBarContainer4的MinContentWidth属性与期待值'360vp'比对
   * 获取sideBarContainer5的MinContentWidth属性与期待值'300px'比对
   * 获取sideBarContainer6的MinContentWidth属性与期待值'100px'比对
   * 获取sideBarContainer7的MinContentWidth属性与期待值'100px'比对
   * 获取sideBarContainer8的MinContentWidth属性与期待值'360vp'比对
   * 点击button，变更sideBarContainer8的minContentWidth属性值为'100px'
   * 获取sideBarContainer8的MinContentWidth属性与期待值'100px'比对
   * 点击button，变更sideBarContainer8的minContentWidth属性值为'100vp'
   * 获取sideBarContainer8的MinContentWidth属性与期待值'100vp'比对
   * 点击button，变更sideBarContainer8的minContentWidth属性值为'100fp'
   * 获取sideBarContainer8的MinContentWidth属性与期待值'100fp'比对
   * 点击button，变更sideBarContainer8的minContentWidth属性值为'100lpx'
   * 获取sideBarContainer8的MinContentWidth属性与期待值'100lpx'比对
   * 点击button，变更sideBarContainer8的minContentWidth属性值为'30%'
   * 获取sideBarContainer8的MinContentWidth属性与期待值'30%'比对
   * 点击button，变更sideBarContainer8的minContentWidth属性值为'$r('app.string.SideBarContainer_size')'
   * 获取sideBarContainer8的MinContentWidth属性与期待值'$r('app.string.SideBarContainer_size')'比对
   */
  defineTest('sideBarContainerMinContentWidthTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerMinContentWidthTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerMinContentWidth1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth1')
      .enabled(true))
    let sideBarContainerMinContentWidth2: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth2')
      .enabled(true))
    let sideBarContainerMinContentWidth3: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth3')
      .enabled(true))
    let sideBarContainerMinContentWidth4: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth4')
      .enabled(true))
    let sideBarContainerMinContentWidth5: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth5')
      .enabled(true))
    let sideBarContainerMinContentWidth6: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth6')
      .enabled(true))
    let sideBarContainerMinContentWidth7: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth7')
      .enabled(true))
    let sideBarContainerMinContentWidth8: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinContentWidth8')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerMinContentWidth')
      .enabled(true)))

    let minContentWidth1: string = await sideBarContainerMinContentWidth1.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth1).$attrs.minContentWidth, '360.000000')

    let minContentWidth2: string = await sideBarContainerMinContentWidth2.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth2).$attrs.minContentWidth, '360.000000')

    let minContentWidth3: string = await sideBarContainerMinContentWidth3.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth3).$attrs.minSideBarWidth, '370.000000')

    let minContentWidth4: string = await sideBarContainerMinContentWidth4.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth4).$attrs.minContentWidth, '360.000000')

    let minContentWidth5: string = await sideBarContainerMinContentWidth5.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth5).$attrs.minContentWidth, '300.000000')

    let minContentWidth6: string = await sideBarContainerMinContentWidth6.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth6).$attrs.minContentWidth, '100.000000')

    let minContentWidth7: string = await sideBarContainerMinContentWidth7.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth7).$attrs.minContentWidth, '100.000000')
    let minContentWidth8: string = await sideBarContainerMinContentWidth8.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth8).$attrs.minContentWidth, '100.000000')
    await button.tap()
    let minContentWidth9: string = await sideBarContainerMinContentWidth8.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth9).$attrs.minContentWidth, '100.000000')
    await button.tap()
    let minContentWidth10: string = await sideBarContainerMinContentWidth8.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth10).$attrs.minContentWidth, '100.000000')
    await button.tap()
    let minContentWidth11: string = await sideBarContainerMinContentWidth8.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth11).$attrs.minContentWidth, '100.000000')
    await button.tap()
    let minContentWidth12: string = await sideBarContainerMinContentWidth8.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth12).$attrs.minContentWidth, '0.300000')
    await button.tap()
    let minContentWidth13: string = await sideBarContainerMinContentWidth8.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth13).$attrs.minContentWidth, $r('app.string.SideBarContainer_size'))
  }, 0)
}
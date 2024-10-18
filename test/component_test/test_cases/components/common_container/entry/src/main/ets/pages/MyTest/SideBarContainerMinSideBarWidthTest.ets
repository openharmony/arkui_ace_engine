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

export default async function sideBarContainerMinSideBarWidthTest() {
  /*
   * SideBarContainer组件 MinSideBarWidth属性
   * 找到id为sideBarContainerMinSideBarWidth1，sideBarContainerMinSideBarWidth2，sideBarContainerMinSideBarWidth3，sideBarContainerMinSideBarWidth4，sideBarContainerMinSideBarWidth5，sideBarContainerMinSideBarWidth6，sideBarContainerMinSideBarWidth7的SideBarContainer组件
   * 找到画面文本为SideBarContainerMinContentWidth的Button组件
   * 获取sideBarContainer1的MinSideBarWidth属性与期待值100比对
   * 获取sideBarContainer2的MinSideBarWidth属性与期待值50比对
   * 获取sideBarContainer3的MinSideBarWidth属性与期待值$r('app.string.SideBarContainer_size')比对
   * 获取sideBarContainer4的MinSideBarWidth属性与期待值100比对
   * 获取sideBarContainer5的MinSideBarWidth属性与期待值'100px'比对
   * 获取sideBarContainer6的MinSideBarWidth属性与期待值'240vp'比对
   * 获取sideBarContainer7的MinSideBarWidth属性与期待值'240vp'比对
   * 点击button，变更sideBarContainer7的minContentWidth属性值为'50px'
   * 获取sideBarContainer7的MinSideBarWidth属性与期待值'50px'比对
   */
  defineTest('sideBarContainerMinSideBarWidthTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerMinSideBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerMinSideBarWidth1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth1')
      .enabled(true))
    let sideBarContainerMinSideBarWidth2: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth2')
      .enabled(true))
    let sideBarContainerMinSideBarWidth3: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth3')
      .enabled(true))
    let sideBarContainerMinSideBarWidth4: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth4')
      .enabled(true))
    let sideBarContainerMinSideBarWidth5: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth5')
      .enabled(true))
    let sideBarContainerMinSideBarWidth6: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth6')
      .enabled(true))
    let sideBarContainerMinSideBarWidth7: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMinSideBarWidth7')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerMinSideBarWidth')
      .enabled(true)))

    let minSideBarWidth1: string = await sideBarContainerMinSideBarWidth1.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth1).$attrs.minSideBarWidth, '100.000000')

    let minSideBarWidth2: string = await sideBarContainerMinSideBarWidth2.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth2).$attrs.minSideBarWidth, '50.000000')

    let minSideBarWidth3: string = await sideBarContainerMinSideBarWidth3.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth3).$attrs.minSideBarWidth, $r('app.string.SideBarContainer_size'))

    let minSideBarWidth4: string = await sideBarContainerMinSideBarWidth4.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth4).$attrs.minSideBarWidth, '200.000000')

    let minSideBarWidth5: string = await sideBarContainerMinSideBarWidth5.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth5).$attrs.minSideBarWidth, '100.000000')

    let minSideBarWidth6: string = await sideBarContainerMinSideBarWidth6.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth6).$attrs.minSideBarWidth, '240.000000')

    let minSideBarWidth7: string = await sideBarContainerMinSideBarWidth7.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth7).$attrs.minSideBarWidth, '240.000000')

    await button.tap()
    let minSideBarWidth8: string = await sideBarContainerMinSideBarWidth7.getInspectorInfo()
    assertEqual(JSON.parse(minSideBarWidth8).$attrs.minSideBarWidth, '50.000000')
  }, 0)
}
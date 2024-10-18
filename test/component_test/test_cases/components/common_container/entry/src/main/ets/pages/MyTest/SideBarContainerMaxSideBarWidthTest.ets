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

export default async function sideBarContainerMaxSideBarWidthTest() {
  /*
   * SideBarContainer组件 MaxSideBarWidth属性
   * 找到id为sideBarContainerMaxSideBarWidth1，sideBarContainerMaxSideBarWidth2，sideBarContainerMaxSideBarWidth3，sideBarContainerMaxSideBarWidth4，sideBarContainerMaxSideBarWidth5，sideBarContainerMaxSideBarWidth6，sideBarContainerMaxSideBarWidth7的SideBarContainer组件
   * 找到画面文本为SideBarContainerMaxSideBarWidth的Button组件
   * 获取sideBarContainerMaxSideBarWidth1的MaxSideBarWidth属性与期待值50比对
   * 获取sideBarContainerMaxSideBarWidth1的SideBarWidth属性与期待值50比对
   * 获取sideBarContainerMaxSideBarWidth2的MaxSideBarWidth属性与期待值50比对
   * 获取sideBarContainerMaxSideBarWidth2的SideBarWidth属性与期待值50比对
   * 获取sideBarContainerMaxSideBarWidth3的MaxSideBarWidth属性与期待值$r('app.string.SideBarContainer_size')比对
   * 获取sideBarContainerMaxSideBarWidth3的SideBarWidth属性与期待值$r('app.string.SideBarContainer_size')比对
   * 获取sideBarContainerMaxSideBarWidth4的MaxSideBarWidth属性与期待值50比对
   * 获取sideBarContainerMaxSideBarWidth4的SideBarWidth属性与期待值50比对
   * 获取sideBarContainerMaxSideBarWidth5的MaxSideBarWidth属性与期待值'200px'比对
   * 获取sideBarContainerMaxSideBarWidth5的SideBarWidth属性与期待值'200px'比对
   * 获取sideBarContainerMaxSideBarWidth6的MaxSideBarWidth属性与期待值'280vp'比对
   * 获取sideBarContainerMaxSideBarWidth6的SideBarWidth属性与期待值'280vp'比对
   * 获取sideBarContainerMaxSideBarWidth7的MaxSideBarWidth属性与期待值'280vp'比对
   * 获取sideBarContainerMaxSideBarWidth7的SideBarWidth属性与期待值'280vp'比对
   * 点击button，变更sideBarContainerMaxSideBarWidth7的MaxSideBarWidth属性值为'50px'
   * 获取sideBarContainerMaxSideBarWidth7的MaxSideBarWidth属性与期待值'50px'比对
   */
  defineTest('sideBarContainerMaxSideBarWidthTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerMaxSideBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerMaxSideBarWidth1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth1')
      .enabled(true))
    let sideBarContainerMaxSideBarWidth2: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth2')
      .enabled(true))
    let sideBarContainerMaxSideBarWidth3: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth3')
      .enabled(true))
    let sideBarContainerMaxSideBarWidth4: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth4')
      .enabled(true))
    let sideBarContainerMaxSideBarWidth5: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth5')
      .enabled(true))
    let sideBarContainerMaxSideBarWidth6: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth6')
      .enabled(true))
    let sideBarContainerMaxSideBarWidth7: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerMaxSideBarWidth7')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerMaxSideBarWidth')
      .enabled(true)))

    let maxSideBarWidth1: string = await sideBarContainerMaxSideBarWidth1.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth1).$attrs.maxSideBarWidth, '50.000000')

    let maxSideBarWidth2: string = await sideBarContainerMaxSideBarWidth2.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth2).$attrs.maxSideBarWidth, '50.000000')

    let maxSideBarWidth3: string = await sideBarContainerMaxSideBarWidth3.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth3).$attrs.maxSideBarWidth, $r('app.string.SideBarContainer_size'))

    let maxSideBarWidth4: string = await sideBarContainerMaxSideBarWidth4.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth4).$attrs.maxSideBarWidth, '200.000000')

    let maxSideBarWidth5: string = await sideBarContainerMaxSideBarWidth5.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth5).$attrs.maxSideBarWidth, '200.000000')

    let maxSideBarWidth6: string = await sideBarContainerMaxSideBarWidth6.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth6).$attrs.maxSideBarWidth, '280.000000')

    let maxSideBarWidth7: string = await sideBarContainerMaxSideBarWidth7.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth7).$attrs.maxSideBarWidth, '280.000000')

    await button.tap()
    let maxSideBarWidth8: string = await sideBarContainerMaxSideBarWidth7.getInspectorInfo()
    assertEqual(JSON.parse(maxSideBarWidth8).$attrs.maxSideBarWidth, '50.000000')
  }, 0)
}
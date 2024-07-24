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

export default async function sideBarContainerSideBarWidthTest() {
  /*
   * SideBarContainer组件 SideBarWidth属性
   * 找到id为sideBarContainer1，sideBarContainer2，sideBarContainer3，sideBarContainer4的SideBarContainer组件
   * 找到画面文本为SideBarContainerSideBarWidth的Button组件
   * 获取sideBarContainer1的SideBarWidth属性与期待值'240vp'比对
   * 获取sideBarContainer2的SideBarWidth属性与期待值$r('app.string.SideBarContainer_size')比对
   * 获取sideBarContainer3的SideBarWidth属性与期待值'240vp'比对
   * 获取sideBarContainer4的SideBarWidth属性与期待值40比对
   * 点击button，变更sideBarContainer4的SideBarWidth属性值为'40px'
   * 获取sideBarContainer4的SideBarWidth属性与期待值'40px'比对
   */
  defineTest('sideBarContainerSideBarWidthTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerSideBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerSideBarWidth1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerSideBarWidth1')
      .enabled(true))
    let sideBarContainerSideBarWidth2: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerSideBarWidth2')
      .enabled(true))
    let sideBarContainerSideBarWidth3: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerSideBarWidth3')
      .enabled(true))
    let sideBarContainerSideBarWidth4: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerSideBarWidth4')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerSideBarWidth')
      .enabled(true)))

    let sideBarWidth1: string = await sideBarContainerSideBarWidth1.getInspectorInfo()
    assertEqual(JSON.parse(sideBarWidth1).$attrs.sideBarWidth, '240.000000')

    let sideBarWidth2: string = await sideBarContainerSideBarWidth2.getInspectorInfo()
    assertEqual(JSON.parse(sideBarWidth2).$attrs.sideBarWidth, $r('app.string.SideBarContainer_size'))

    let sideBarWidth3: string = await sideBarContainerSideBarWidth3.getInspectorInfo()
    assertEqual(JSON.parse(sideBarWidth3).$attrs.sideBarWidth, '240.000000')

    let sideBarWidth4: string = await sideBarContainerSideBarWidth4.getInspectorInfo()
    assertEqual(JSON.parse(sideBarWidth4).$attrs.sideBarWidth, '40.000000')
    await button.tap()
    let sideBarWidth5: string = await sideBarContainerSideBarWidth4.getInspectorInfo()
    assertEqual(JSON.parse(sideBarWidth5).$attrs.sideBarWidth, '40.000000')
  }, 0)
}
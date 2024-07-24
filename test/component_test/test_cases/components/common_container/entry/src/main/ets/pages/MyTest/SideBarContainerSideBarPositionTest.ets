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

export default async function sideBarContainerSideBarPositionTest() {
  /*
   * SideBarContainer组件 SideBarPosition属性
   * 找到id为sideBarContainerSideBarPosition1的SideBarContainer组件
   * 找到画面文本为SideBarContainerSideBarPosition的Button组件
   * 获取sideBarContainer1的SideBarPosition属性与期待值SideBarPosition.Start比对
   * 点击button，变更sideBarContainer1的SideBarPosition属性值为SideBarPosition.End
   * 获取sideBarContainer1的SideBarPosition属性与期待值SideBarPosition.End比对
   */
  defineTest('sideBarContainerSideBarPositionTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerSideBarPositionTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerSideBarPosition1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerSideBarPosition1')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerSideBarPosition')
      .enabled(true)))

    let sideBarPosition1: string = await sideBarContainerSideBarPosition1.getInspectorInfo()
    assertEqual(JSON.parse(sideBarPosition1).$attrs.sideBarPosition, 'SideBarPosition.Start')
    await button.tap()
    let sideBarPosition2: string = await sideBarContainerSideBarPosition1.getInspectorInfo()
    assertEqual(JSON.parse(sideBarPosition2).$attrs.sideBarPosition, 'SideBarPosition.End')
  }, 0)
}
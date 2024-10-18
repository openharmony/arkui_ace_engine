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

export default async function sideBarContainerDividerTest() {
  /*
   * SideBarContainer组件 Divider属性
   * 找到id为sideBarContainerDivider1，sideBarContainerDivider2，sideBarContainerDivider3，sideBarContainerDivider4，sideBarContainerDivider5的SideBarContainer组件
   * 找到画面文本为SideBarContainerDivider的Button组件
   * 获取sideBarContainer1的Divider属性与期待值{strokeWidth:$r('app.string.pixel_size'),color:'rgb(255, 0, 0)',startMargin:$r('app.string.pixel_size'),endMargin:$r('app.string.pixel_size')}比对
   * 获取sideBarContainer2的Divider属性与期待值{strokeWidth:$r('app.string.pixel_size'),color:'rgb(255, 0, 0, 0.5)',startMargin:$r('app.string.pixel_size'),endMargin:$r('app.string.pixel_size')}比对
   * 获取sideBarContainer3的Divider属性与期待值{strokeWidth:$r('app.string.pixel_size'),color:$r('sys.color.ohos_fa_palette1'),startMargin:$r('app.string.pixel_size'),endMargin:$r('app.string.pixel_size')}比对
   * 获取sideBarContainer4的Divider属性与期待值null比对
   * 获取sideBarContainer5的Divider属性与期待值{strokeWidth:5,color:Color.Red,startMargin:10,endMargin:10}比对
   * 点击button，变更sideBarContainer5的Divider属性值为{strokeWidth:'5px',color:0x0000ff,startMargin:'10px',endMargin:'10px'}
   * 获取sideBarContainer5的Divider属性与期待值{strokeWidth:'5px',color:0x0000ff,startMargin:'10px',endMargin:'10px'}比对
   */
  defineTest('sideBarContainerDividerTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerDividerTestDemo running')
    let driver: Tester = Tester.create()

    let sideBarContainerDivider1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerDivider1')
      .enabled(true))
    let sideBarContainerDivider2: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerDivider2')
      .enabled(true))
    let sideBarContainerDivider3: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerDivider3')
      .enabled(true))
    let sideBarContainerDivider4: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerDivider4')
      .enabled(true))
    let sideBarContainerDivider5: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerDivider5')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerDivider')
      .enabled(true)))

    let divider1: string = await sideBarContainerDivider1.getInspectorInfo()
    assertEqual(JSON.parse(divider1).$attrs.divider,
      '{"strokeWidth":"20.00px","startMargin":"20.00px","endMargin":"20.00px","color":"#FFFF0000"}')

    let divider2: string = await sideBarContainerDivider2.getInspectorInfo()
    assertEqual(JSON.parse(divider2).$attrs.divider,
      '{"strokeWidth":"20.00px","startMargin":"20.00px","endMargin":"20.00px","color":"#08000000"}')

    let divider3: string = await sideBarContainerDivider3.getInspectorInfo()
    assertEqual(JSON.parse(divider3).$attrs.divider,
      '{"strokeWidth":"20.00px","startMargin":"20.00px","endMargin":"20.00px","color":"#FF3F56EA"}')

    let divider4: string = await sideBarContainerDivider4.getInspectorInfo()
    assertEqual(JSON.parse(divider4).$attrs.divider,
      '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#08000000"}')

    let divider5: string = await sideBarContainerDivider5.getInspectorInfo()
    assertEqual(JSON.parse(divider5).$attrs.divider,
      '{"strokeWidth":"5.00vp","startMargin":"10.00vp","endMargin":"10.00vp","color":"#FFFF0000"}')

    await button.tap()
    let divider6: string = await sideBarContainerDivider5.getInspectorInfo()
    assertEqual(JSON.parse(divider6).$attrs.divider,
      '{"strokeWidth":"5.00px","startMargin":"10.00px","endMargin":"10.00px","color":"#FF0000FF"}')
  }, 0)
}
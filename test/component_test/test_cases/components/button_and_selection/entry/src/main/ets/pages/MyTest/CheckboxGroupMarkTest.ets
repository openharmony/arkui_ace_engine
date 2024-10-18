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

export default async function checkboxGroupMarkTest() {
  /*
   * CheckboxGroup组件 Mark属性
   * 找到画面id为checkboxGroupMark1，checkboxGroupMark2，checkboxGroupMark3，checkboxGroupMark4，checkboxGroupMark5的CheckboxGroup组件
   * 找到画面文本为CheckboxGroupMark1，CheckboxGroupMark2的Button组件
   * 获取checkboxGroupMark1的Mark属性与期待值{strokeColor: Color.Black}比对
   * 获取checkboxGroupMark2的Mark属性与期待值{strokeColor: '#FFA52A2A'}比对
   * 获取checkboxGroupMark3的Mark属性与期待值{strokeColor: '#FF8EFF65'}比对
   * 获取checkboxGroupMark4的Mark属性与期待值{size: '10.00px',strokeWidth: '10.00px'}比对
   * 获取checkboxGroupMark5的Mark属性与期待值{size: '50.00vp',strokeWidth: '50.00vp'}比对
   * 点击button1，变更checkboxGroupMark3的Mark属性值为{strokeColor: $r('sys.color.ohos_fa_palette1')}
   * 获取checkboxGroupMark3的Mark属性与期待值{strokeColor: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更checkboxGroupMark5的Mark属性值为{size: $r('app.string.mark_strok'),strokeWidth: $r('app.string.mark_strok')}
   * 获取checkboxGroupMark5的Mark属性与期待值{size: $r('app.string.mark_strok'),strokeWidth: $r('app.string.mark_strok')}比对
   */
  defineTest('checkboxGroupMarkTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxGroupMarkTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxGroupMark1: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupMark1').enabled(true))
    let checkboxGroupMark2: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupMark2').enabled(true))
    let checkboxGroupMark3: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupMark3').enabled(true))
    let checkboxGroupMark4: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupMark4').enabled(true))
    let checkboxGroupMark5: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupMark5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CheckboxGroupMark1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CheckboxGroupMark2').enabled(true))

    let mark1: string = await checkboxGroupMark1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark1).$attrs.mark).strokeColor.toLowerCase(), Color.Black)

    let mark2: string = await checkboxGroupMark2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark2).$attrs.mark).strokeColor, '#FFA52A2A')

    let mark3: string = await checkboxGroupMark3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark3).$attrs.mark).strokeColor, '#FF8EFF65')

    let mark4: string = await checkboxGroupMark4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark4).$attrs.mark).size, '10.00px')
    assertEqual(JSON.parse(JSON.parse(mark4).$attrs.mark).strokeWidth, '10.00px')

    let mark5: string = await checkboxGroupMark5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark5).$attrs.mark).size, '50.00vp')
    assertEqual(JSON.parse(JSON.parse(mark5).$attrs.mark).strokeWidth, '50.00vp')

    await button1.tap()
    let mark6: string = await checkboxGroupMark3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark6).$attrs.mark).strokeColor, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let mark7: string = await checkboxGroupMark5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark7).$attrs.mark).size, $r('app.string.mark_strok'))
    assertEqual(JSON.parse(JSON.parse(mark7).$attrs.mark).strokeWidth, $r('app.string.mark_strok'))
  }, 0)
}
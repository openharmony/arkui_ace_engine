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

export default async function checkboxMarkTest() {
  /*
   * Checkbox组件 Mark属性
   * 找到画面id为checkboxMark1，checkboxMark2，checkboxMark3，checkboxMark4，checkboxMark5的Checkbox组件
   * 找到画面文本为CheckboxMark1，CheckboxMark2的Button组件
   * 获取checkboxMark1的Mark属性与期待值{strokeColor: Color.Black}比对
   * 获取checkboxMark2的Mark属性与期待值{strokeColor: '#FFA52A2A'}比对
   * 获取checkboxMark3的Mark属性与期待值{strokeColor: '#FF8EFF65'}比对
   * 获取checkboxMark4的Mark属性与期待值{size: '10.00px',strokeWidth: '10.00px'}比对
   * 获取checkboxMark5的Mark属性与期待值{size: '50.00vp',strokeWidth: '50.00vp'}比对
   * 点击button1，变更checkboxMark3的Mark属性值为{strokeColor: $r('sys.color.ohos_fa_palette1')}
   * 获取checkboxMark3的Mark属性与期待值{strokeColor: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更checkboxMark5的Mark属性值为{size: $r('app.string.mark_strok'),strokeWidth: $r('app.string.mark_strok')}
   * 获取checkboxMark5的Mark属性与期待值{size: $r('app.string.mark_strok'),strokeWidth: $r('app.string.mark_strok')}比对
   */
  defineTest('checkboxMarkTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxMarkTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxMark1: Component = await driver.findComponent(Matcher.create().id('checkboxMark1').enabled(true))
    let checkboxMark2: Component = await driver.findComponent(Matcher.create().id('checkboxMark2').enabled(true))
    let checkboxMark3: Component = await driver.findComponent(Matcher.create().id('checkboxMark3').enabled(true))
    let checkboxMark4: Component = await driver.findComponent(Matcher.create().id('checkboxMark4').enabled(true))
    let checkboxMark5: Component = await driver.findComponent(Matcher.create().id('checkboxMark5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CheckboxMark1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CheckboxMark2').enabled(true))

    let mark1: string = await checkboxMark1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark1).$attrs.mark).strokeColor.toLowerCase(), Color.Black)

    let mark2: string = await checkboxMark2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark2).$attrs.mark).strokeColor, '#FFA52A2A')

    let mark3: string = await checkboxMark3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark3).$attrs.mark).strokeColor, '#FF8EFF65')

    let mark4: string = await checkboxMark4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark4).$attrs.mark).size, '10.00px')
    assertEqual(JSON.parse(JSON.parse(mark4).$attrs.mark).strokeWidth, '10.00px')

    let mark5: string = await checkboxMark5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark5).$attrs.mark).size, '50.00vp')
    assertEqual(JSON.parse(JSON.parse(mark5).$attrs.mark).strokeWidth, '50.00vp')

    await button1.tap()
    let mark6: string = await checkboxMark3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark6).$attrs.mark).strokeColor, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let mark7: string = await checkboxMark5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(mark7).$attrs.mark).size, $r('app.string.mark_strok'))
    assertEqual(JSON.parse(JSON.parse(mark7).$attrs.mark).strokeWidth, $r('app.string.mark_strok'))
  }, 0)
}
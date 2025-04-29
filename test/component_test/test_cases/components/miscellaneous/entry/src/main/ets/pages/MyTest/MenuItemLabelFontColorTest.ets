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

export default async function menuItemLabelFontColorTest() {
  /*
 * MenuItem组件 LabelFontColor属性
 * 找到画面id为menuItemLabelFontColor1,menuItemLabelFontColor2的MenuItem组件
 * 找到画面文本为MenuItemLabelFontColor1的Button1组件
 * 找到画面文本为MenuItemLabelFontColor2的Button2组件
 * 获取menuItemLabelFontColor1的LabelFontColor属性与期待值Color.Pink比对
 * 点击button1，变更menuItemLabelFontColor1的LabelFontColor属性值为$r('sys.color.ohos_fa_activated')
 * 获取menuItemLabelFontColor1的LabelFontColor属性与期待值$r('sys.color.ohos_fa_activated')比对
 * 点击button2，变更menuItemLabelFontColor1的LabelFontColor属性值为0xfff000
 * 获取menuItemLabelFontColor1的LabelFontColor属性与期待值'#FFFFF000'比对
 * 获取menuItemLabelFontColor2的LabelFontColor属性与期待值'#FFFF79F2'比对
 */
  defineTest('menuItemLabelFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuItemLabelFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let menuItemLabelFontColor1: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFontColor1').enabled(true))
    let menuItemLabelFontColor2: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFontColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuItemLabelFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuItemLabelFontColor2').enabled(true))

    let labelFontColor1: string = await menuItemLabelFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(labelFontColor1).$attrs.labelFontColor.toLowerCase(), Color.Pink)

    await button1.tap()
    let labelFontColor2: string = await menuItemLabelFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(labelFontColor2).$attrs.labelFontColor, $r('sys.color.ohos_fa_activated'))

    await button2.tap()
    let labelFontColor3: string = await menuItemLabelFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(labelFontColor3).$attrs.labelFontColor, '#FFFFF000')

    let labelFontColor4: string = await menuItemLabelFontColor2.getInspectorInfo()
    assertEqual(JSON.parse(labelFontColor4).$attrs.labelFontColor, '#FFFF79F2')
  }, 0)
}
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

export default async function menuItemLabelFontTest() {
  /*
 * MenuItem组件 LabelFont属性
 * 找到画面id为menuItemLabelFont1,menuItemLabelFont2,menuItemLabelFont3,menuItemLabelFont4,menuItemLabelFont5,menuItemLabelFont6的MenuItem组件
 * 找到画面文本为MenuItemLabelFont1的Button1组件
 * 找到画面文本为MenuItemLabelFont2的Button2组件
 * 获取menuItemLabelFont1的{ LabelFont.Size,LabelFont.Weight,LabelFont.Family,LabelFont.Style }属性与期待值{'20.00fp',500,'Arial',FontStyle.Normal }比对
 * 点击button1，变更menuItemLabelFont1的LabelFont属性值为{$r('app.string.font_size'),FontWeight.Bolder,'Arial',FontStyle.Normal }
 * 获取menuItemLabelFont1的{ LabelFont.Size,LabelFont.Weight,LabelFont.Family,LabelFont.Style属性与期待值$r('app.string.font_size'),FontWeight.Bolder,'Arial',FontStyle.Normal }比对
 * 点击button2，变更menuItemLabelFont1的LabelFont.Weight属性值为FontWeight.Bold
 * 获取menuItemLabelFont1的LabelFont.Weight属性与期待值FontWeight.Bold比对
 * 获取menuItemLabelFont2的{ LabelFont.Size,ContentFont.Weight,ContentFont.Family,ContentFont.Style }属性与期待值{ '30.00px','200','TESTFONTRawFile',FontStyle.Italic }比对
 * 获取menuItemLabelFont3的LabelFont.Weight属性与期待值FontWeight.Lighter比对
 * 获取menuItemLabelFont4的LabelFont.Weight属性与期待值FontWeight.Normal比对
 * 获取menuItemLabelFont5的LabelFont.Weight属性与期待值FontWeight.Regular比对
 * 获取menuItemLabelFont6的LabelFont.Weight属性与期待值FontWeight.Medium比对
 */
  defineTest('menuItemLabelFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuItemLabelFontTestDemo running')
    let driver: Tester = Tester.create()
    let menuItemLabelFont1: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFont1').enabled(true))
    let menuItemLabelFont2: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFont2').enabled(true))
    let menuItemLabelFont3: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFont3').enabled(true))
    let menuItemLabelFont4: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFont4').enabled(true))
    let menuItemLabelFont5: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFont5').enabled(true))
    let menuItemLabelFont6: Component =
      await driver.findComponent(Matcher.create().id('menuItemLabelFont6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuItemLabelFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuItemLabelFont2').enabled(true))

    let labelFont1: string = await menuItemLabelFont1.getInspectorInfo()
    assertEqual(JSON.parse(labelFont1).$attrs.labelFont.size, '20.00fp')
    assertEqual(JSON.parse(labelFont1).$attrs.labelFont.weight, '500')
    assertEqual(JSON.parse(labelFont1).$attrs.labelFont.family, 'Arial')
    assertEqual(JSON.parse(labelFont1).$attrs.labelFont.style, 'FontStyle.Normal')

    await button1.tap()
    let labelFont2: string = await menuItemLabelFont1.getInspectorInfo()
    assertEqual(JSON.parse(labelFont2).$attrs.labelFont.size, $r('app.string.font_size'))
    assertEqual(JSON.parse(labelFont2).$attrs.labelFont.weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(labelFont2).$attrs.labelFont.family, 'Arial')
    assertEqual(JSON.parse(labelFont2).$attrs.labelFont.style, 'FontStyle.Normal')

    await button2.tap()
    let labelFont3: string = await menuItemLabelFont1.getInspectorInfo()
    assertEqual(JSON.parse(labelFont3).$attrs.labelFont.weight, 'FontWeight.Bold')

    let labelFont4: string = await menuItemLabelFont2.getInspectorInfo()
    assertEqual(JSON.parse(labelFont4).$attrs.labelFont.size, '30.00px')
    assertEqual(JSON.parse(labelFont4).$attrs.labelFont.weight, '200')
    assertEqual(JSON.parse(labelFont4).$attrs.labelFont.family, 'TESTFONTRawFile')
    assertEqual(JSON.parse(labelFont4).$attrs.labelFont.style, 'FontStyle.Italic')

    let labelFont5: string = await menuItemLabelFont3.getInspectorInfo()
    assertEqual(JSON.parse(labelFont5).$attrs.labelFont.weight, 'FontWeight.Lighter')

    let labelFont6: string = await menuItemLabelFont4.getInspectorInfo()
    assertEqual(JSON.parse(labelFont6).$attrs.labelFont.weight, 'FontWeight.Normal')

    let labelFont7: string = await menuItemLabelFont5.getInspectorInfo()
    assertEqual(JSON.parse(labelFont7).$attrs.labelFont.weight, 'FontWeight.Regular')

    let labelFont8: string = await menuItemLabelFont6.getInspectorInfo()
    assertEqual(JSON.parse(labelFont8).$attrs.labelFont.weight, 'FontWeight.Medium')
  }, 0)
}
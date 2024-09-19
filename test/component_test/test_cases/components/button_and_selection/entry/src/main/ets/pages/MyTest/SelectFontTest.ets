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

export default async function selectFontTest() {
  /*
   * Select组件 Font属性
   * 找到画面id为selectFont1，selectFont2，selectFont3，...，selectFont6，selectFont7的Select组件
   * 找到画面文本为SelectFont的Button组件
   * 获取selectFont1的Font属性与期待值{ weight: 'FontWeight.Lighter' }比对
   * 获取selectFont2的Font属性与期待值{ weight: 'FontWeight.Normal' }比对
   * 获取selectFont3的Font属性与期待值{ weight: 'FontWeight.Regular', size: '0.00fp' }比对
   * 获取selectFont4的Font属性与期待值{ weight: 'FontWeight.Medium', size: '16.00fp' }对比
   * 获取selectFont5的Font属性与期待值{ weight: 'FontWeight.Bold', size: $r('app.string.size') }对比
   * 获取selectFont6的Font属性与期待值{ weight: 'FontWeight.Bolder', size: '10.00fp', family: 'Arial' }对比
   * 获取selectFont7的Font属性与期待值{ weight: '100', size: '20.00fp', family: 'TESTFONT',style: 'FontStyle.Normal' }对比
   * 点击button，变更selectFont7的Font属性值为{ weight: '200', size: '40.00fp', style: 'FontStyle.Italic' }
   * 获取selectFont7的Font属性与期待值{ weight: '200', size: '40.00fp', style: 'FontStyle.Italic' }比对
   */
  defineTest('selectFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectFontTestDemo running')
    let driver: Tester = Tester.create()
    let selectFont1: Component = await driver.findComponent(Matcher.create().id('selectFont1').enabled(true))
    let selectFont2: Component = await driver.findComponent(Matcher.create().id('selectFont2').enabled(true))
    let selectFont3: Component = await driver.findComponent(Matcher.create().id('selectFont3').enabled(true))
    let selectFont4: Component = await driver.findComponent(Matcher.create().id('selectFont4').enabled(true))
    let selectFont5: Component = await driver.findComponent(Matcher.create().id('selectFont5').enabled(true))
    let selectFont6: Component = await driver.findComponent(Matcher.create().id('selectFont6').enabled(true))
    let selectFont7: Component = await driver.findComponent(Matcher.create().id('selectFont7').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectFont').enabled(true))

    let font1: string = await selectFont1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font1).$attrs.font).weight, 'FontWeight.Lighter')

    let font2: string = await selectFont2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font2).$attrs.font).weight, 'FontWeight.Normal')

    let font3: string = await selectFont3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font3).$attrs.font).weight, 'FontWeight.Regular')
    assertEqual(JSON.parse(JSON.parse(font3).$attrs.font).size, '0.00fp')

    let font4: string = await selectFont4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font4).$attrs.font).weight, 'FontWeight.Medium')
    assertEqual(JSON.parse(JSON.parse(font4).$attrs.font).size, '16.00fp')

    let font5: string = await selectFont5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font5).$attrs.font).weight, 'FontWeight.Bold')
    assertEqual(JSON.parse(JSON.parse(font5).$attrs.font).size, $r('app.string.size'))

    let font6: string = await selectFont6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font6).$attrs.font).weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(JSON.parse(font6).$attrs.font).size, '10.00fp')
    assertEqual(JSON.parse(JSON.parse(font6).$attrs.font).family, 'Arial')

    let font7: string = await selectFont7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font7).$attrs.font).weight, '100')
    assertEqual(JSON.parse(JSON.parse(font7).$attrs.font).size, '20.00fp')
    assertEqual(JSON.parse(JSON.parse(font7).$attrs.font).family, 'TESTFONT')
    assertEqual(JSON.parse(JSON.parse(font7).$attrs.font).style, 'FontStyle.Normal')

    await button.tap()
    let font8: string = await selectFont7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(font8).$attrs.font).weight, '200')
    assertEqual(JSON.parse(JSON.parse(font8).$attrs.font).size, '40.00fp')
    assertEqual(JSON.parse(JSON.parse(font8).$attrs.font).style, 'FontStyle.Italic')
  }, 0)
}
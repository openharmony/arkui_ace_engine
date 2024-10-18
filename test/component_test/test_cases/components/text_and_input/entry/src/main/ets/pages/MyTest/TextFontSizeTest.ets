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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textFontSizeTest() {
  /*
   * Text组件 FontSize属性
   * 找到画面id为textFontSize1,textFontSize的Text组件
   * 找到画面文本为TextFontSize的Button组件
   * 获取text1的FontSize属性与期待值$r('app.string.text')比对
   * 获取text2的FontSize属性与期待值50比对
   * 点击button，变更text2的FontSize属性值为'100px'
   * 获取text2的FontSize属性与期待值'100px'比对
   */
  defineTest('textFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textFontSizeTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textFontSize1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textFontSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextFontSize').enabled(true))

    let fontSize1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, $r('app.string.fp_text'))
    let fontSize2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, '50.00fp')

    await button.tap()
    let fontSize3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, '100.00px')
  }, 0)
}
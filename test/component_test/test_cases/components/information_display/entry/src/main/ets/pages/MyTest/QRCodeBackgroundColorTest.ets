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

export default async function qRCodeBackgroundColorTest() {
  /*
   * QRCode组件 BackgroundColor属性
   * 找到画面id为qRCodeBackgroundColor1,qRCodeBackgroundColor2的QRCode组件
   * 找到画面文本为QRCodeBackgroundColor1,QRCodeBackgroundColor2的Button组件
   * 获取qRCode1的BackgroundColor属性与期待值Color.Orange比对
   * 获取qRCode2的BackgroundColor属性与期待值0x00FFFF比对
   * 点击button1，变更qRCode1的BackgroundColor属性值为"#ffc007f3"
   * 获取qRCode1的BackgroundColor属性与期待值"#ffc007f3"比对
   * 点击button2，变更cqRCode1的BackgroundColor属性值为$r('app.color.data_panel_resource_color6')
   * 获取qRCode1的BackgroundColor属性与期待值$r('app.color.data_panel_resource_color6')比对
   */
  defineTest('qRCodeBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('qRCodeBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let qRCode1: Component = await driver.findComponent(Matcher.create().id('qRCodeBackgroundColor1').enabled(true))
    let qRCode2: Component = await driver.findComponent(Matcher.create().id('qRCodeBackgroundColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('QRCodeBackgroundColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('QRCodeBackgroundColor2').enabled(true))
    let codeBackgroundColor1: string = await qRCode1.getInspectorInfo()
    assertEqual(JSON.parse(codeBackgroundColor1).$attrs.backgroundColor.toLowerCase(), Color.Orange)
    let codeBackgroundColor2: string = await qRCode2.getInspectorInfo()
    assertEqual(JSON.parse(codeBackgroundColor2).$attrs.backgroundColor, '#FF00FFFF')
    await button1.tap()
    let codeBackgroundColor3: string = await qRCode1.getInspectorInfo()
    assertEqual(JSON.parse(codeBackgroundColor3).$attrs.backgroundColor.toLowerCase(), "#ffc007f3")
    await button2.tap()
    let codeBackgroundColor4: string = await qRCode1.getInspectorInfo()
    assertEqual(JSON.parse(codeBackgroundColor4).$attrs.backgroundColor, $r('app.color.data_panel_resource_color6'))
  }, 0)
}
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

export default async function qRCodeColorTest() {
  /*
   * QRCode组件 Color属性
   * 找到画面id为qRCodeColor1,qRCodeColor2的QRCode组件
   * 找到画面文本为QRCodeColor1,QRCodeColor2的Button组件
   * 获取qRCode1的color属性值与期待值Color.Red比对
   * 获取qRCode2的color属性值与期待值0xFFFF00比对
   * 点击button1，变更qRCode1的color属性值为"#ffc007f3"
   * 获取qRCode1的color属性值与期待值"#ffc007f3"比对
   * 点击button2，变更qRCode1的color属性值为$r('app.color.data_panel_resource_color8')
   * 获取qRCode1的color属性值与期待值$r('app.color.data_panel_resource_color8')比对
   */
  defineTest('qRCodeColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('qRCodeColorTestDemo running')
    let driver: Tester = Tester.create()
    let qRCode1: Component = await driver.findComponent(Matcher.create().id('qRCodeColor1').enabled(true))
    let qRCode2: Component = await driver.findComponent(Matcher.create().id('qRCodeColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('QRCodeColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('QRCodeColor2').enabled(true))
    let color1: string = await qRCode1.getInspectorInfo()
    assertEqual(JSON.parse(color1).$attrs.color.toLowerCase(), Color.Red)
    let color2: string = await qRCode2.getInspectorInfo()
    assertEqual(JSON.parse(color2).$attrs.color, '#FFFFFF00')
    await button1.tap()
    let color3: string = await qRCode1.getInspectorInfo()
    assertEqual(JSON.parse(color3).$attrs.color.toLowerCase(), "#ffc007f3")
    await button2.tap()
    let color4: string = await qRCode1.getInspectorInfo()
    assertEqual(JSON.parse(color4).$attrs.color, $r('app.color.data_panel_resource_color8'))
  }, 0)
}
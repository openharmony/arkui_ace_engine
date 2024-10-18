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

export default async function textClockTextShadowOptionsTest() {
  /*
  * TextClock组件 TextShadowOptions属性
  * 找到画面id为textClockTextShadowOptions1，textClockTextShadowOptions2，textClockTextShadowOptions3的TextClock组件
  * 找到画面文本为TextClockTextShadowOptions1，TextClockTextShadowOptions2，TextClockTextShadowOptions3的Button组件
  * 获取textClock1的TextShadowOptions属性数组第0位的radius参数与期待值$r('app.integer.data_panel_number')比对
  * 获取textClock1的TextShadowOptions属性数组第0位的type参数与期待值ShadowType.BLUR比对
  * 获取textClock1的TextShadowOptions属性数组第0位的color参数与期待值"#800080"比对
  * 获取textClock1的TextShadowOptions属性数组第0位的offsetX参数与期待值$r('app.integer.data_panel_offset_radius1')比对
  * 获取textClock1的TextShadowOptions属性数组第0位的offsetY参数与期待值$r('app.integer.data_panel_offset_radius1')比对
  * 获取textClock1的TextShadowOptions属性数组第1位的radius参数与期待值$r('app.integer.data_panel_number')比对
  * 获取textClock1的TextShadowOptions属性数组第1位的type参数与期待值ShadowType.BLUR比对
  * 获取textClock1的TextShadowOptions属性数组第1位的color参数与期待值"#FF4500"比对
  * 获取textClock1的TextShadowOptions属性数组第1位的offsetX参数与期待值$r('app.integer.data_panel_offset_radius2')比对
  * 获取textClock1的TextShadowOptions属性数组第1位的offsetY参数与期待值$r('app.integer.data_panel_offset_radius2')比对
  * 获取textClock2的TextShadowOptions属性数组第0位的radius参数与期待值10比对
  * 获取textClock2的TextShadowOptions属性数组第0位的type参数与期待值ShadowType.COLOR比对
  * 获取textClock2的TextShadowOptions属性数组第0位的color参数与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
  * 获取textClock2的TextShadowOptions属性数组第0位的offsetX参数与期待值10比对
  * 获取textClock2的TextShadowOptions属性数组第0位的offsetY参数与期待值10比对
  * 获取textClock2的TextShadowOptions属性数组第1位的radius参数与期待值10比对
  * 获取textClock2的TextShadowOptions属性数组第1位的type参数与期待值ShadowType.COLOR比对
  * 获取textClock2的TextShadowOptions属性数组第1位的color参数与期待值$r('sys.color.ohos_id_color_text_tertiary')比对
  * 获取textClock2的TextShadowOptions属性数组第1位的offsetX参数与期待值30比对
  * 获取textClock2的TextShadowOptions属性数组第1位的offsetY参数与期待值30比对
  * 获取textClock3的TextShadowOptions属性的radius参数与期待值$r('app.integer.data_panel_number')比对
  * 获取textClock3的TextShadowOptions属性的type参数与期待值ShadowType.BLUR比对
  * 获取textClock3的TextShadowOptions属性的color参数与期待值"#800080"比对
  * 获取textClock3的TextShadowOptions属性的offsetX参数与期待值$r('app.integer.data_panel_offset_radius1')比对
  * 获取textClock3的TextShadowOptions属性的offsetY参数与期待值$r('app.integer.data_panel_offset_radius1')比对
  * 点击button1，变更textClock1的TextShadowOptions属性值为{ radius: 10, type: ShadowType.COLOR, color: $r('app.color.data_panel_resource_color2'), offsetX: 30, offsetY: 30 }
  * 获取textClock1的TextShadowOptions属性的radius参数与期待值10比对
  * 获取textClock1的TextShadowOptions属性的type参数与期待值ShadowType.COLOR比对
  * 获取textClock1的TextShadowOptions属性的color参数与期待值$r('app.color.data_panel_resource_color2')比对
  * 获取textClock1的TextShadowOptions属性的offsetX参数与期待值30比对
  * 获取textClock1的TextShadowOptions属性的offsetY参数与期待值30比对
  * 点击button2，变更textClock1的TextShadowOptions属性值为[{ radius: 10, type: ShadowType.COLOR, color: Color.Red, offsetX: 10, offsetY: 10 }, { radius: 10, type: ShadowType.COLOR, color: Color.Yellow, offsetX: 30, offsetY: 30 }]
  * 获取textClock1的TextShadowOptions属性数组第0位的radius参数与期待值10比对
  * 获取textClock1的TextShadowOptions属性数组第0位的type参数与期待值ShadowType.COLOR比对
  * 获取textClock1的TextShadowOptions属性数组第0位的color参数与期待值Color.Red比对
  * 获取textClock1的TextShadowOptions属性数组第0位的offsetX参数与期待值10比对
  * 获取textClock1的TextShadowOptions属性数组第0位的offsetY参数与期待值10比对
  * 获取textClock1的TextShadowOptions属性数组第1位的radius参数与期待值10比对
  * 获取textClock1的TextShadowOptions属性数组第1位的type参数与期待值ShadowType.COLOR比对
  * 获取textClock1的TextShadowOptions属性数组第1位的color参数与期待值Color.Yellow比对
  * 获取textClock1的TextShadowOptions属性数组第1位的offsetX参数与期待值30比对
  * 获取textClock1的TextShadowOptions属性数组第1位的offsetY参数与期待值30比对
  * 点击button3，变更textClock1的TextShadowOptions属性值为{ radius: 10, type: ShadowType.COLOR, color: Color.Blue, offsetX: 30, offsetY: 30 }
  * 获取textClock1的TextShadowOptions属性的radius参数与期待值10比对
  * 获取textClock1的TextShadowOptions属性的type参数与期待值ShadowType.COLOR比对
  * 获取textClock1的TextShadowOptions属性的color参数与期待值Color.Blue比对
  * 获取textClock1的TextShadowOptions属性的offsetX参数与期待值30比对
  * 获取textClock1的TextShadowOptions属性的offsetY参数与期待值30比对
  */
  defineTest('textClockTextShadowOptionsTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockTextShadowOptionsTest running')
    let driver: Tester = Tester.create()
    let textClock1: Component =
      await driver.findComponent(Matcher.create().id('textClockTextShadowOptions1').enabled(true))
    let textClock2: Component =
      await driver.findComponent(Matcher.create().id('textClockTextShadowOptions2').enabled(true))
    let textClock3: Component =
      await driver.findComponent(Matcher.create().id('textClockTextShadowOptions3').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextClockTextShadowOptions1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextClockTextShadowOptions2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('TextClockTextShadowOptions3').enabled(true))
    let textShadowOptions1: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[0].radius, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[0].type, ShadowType.BLUR)
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[0].color, "#800080")
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[0].offsetX,
      $r('app.string.data_panel_offset_radius1'))
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[0].offsetY,
      $r('app.string.data_panel_offset_radius1'))
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[1].radius, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[1].type, ShadowType.BLUR)
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[1].color, "#FF4500")
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[1].offsetX,
      $r('app.string.data_panel_offset_radius2'))
    assertEqual(JSON.parse(textShadowOptions1).$attrs.textShadow[1].offsetY,
      $r('app.string.data_panel_offset_radius2'))
    let textShadowOptions2: string = await textClock2.getInspectorInfo()
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[0].radius, 10)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[0].type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[0].color, $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[0].offsetX, 10)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[0].offsetY, 10)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[1].radius, 10)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[1].type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[1].color, $r('sys.color.ohos_id_color_text_tertiary'))
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[1].offsetX, 30)
    assertEqual(JSON.parse(textShadowOptions2).$attrs.textShadow[1].offsetY, 30)
    let textShadowOptions3: string = await textClock3.getInspectorInfo()
    assertEqual(JSON.parse(textShadowOptions3).$attrs.textShadow.radius, $r("app.string.data_panel_number"))
    assertEqual(JSON.parse(textShadowOptions3).$attrs.textShadow.type, ShadowType.BLUR)
    assertEqual(JSON.parse(textShadowOptions3).$attrs.textShadow.color, "#800080")
    assertEqual(JSON.parse(textShadowOptions3).$attrs.textShadow.offsetX, $r('app.string.data_panel_offset_radius1'))
    assertEqual(JSON.parse(textShadowOptions3).$attrs.textShadow.offsetY, $r('app.string.data_panel_offset_radius1'))
    await button1.tap()
    let textShadowOptions4: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(textShadowOptions4).$attrs.textShadow.radius, 10)
    assertEqual(JSON.parse(textShadowOptions4).$attrs.textShadow.type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadowOptions4).$attrs.textShadow.color, $r('app.color.data_panel_resource_color2'))
    assertEqual(JSON.parse(textShadowOptions4).$attrs.textShadow.offsetX, 30)
    assertEqual(JSON.parse(textShadowOptions4).$attrs.textShadow.offsetY, 30)
    await button2.tap()
    let textShadowOptions5: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[0].radius, 10)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[0].type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[0].color, Color.Red)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[0].offsetX, 10)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[0].offsetY, 10)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[1].radius, 10)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[1].type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[1].color, Color.Yellow)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[1].offsetX, 30)
    assertEqual(JSON.parse(textShadowOptions5).$attrs.textShadow[1].offsetY, 30)
    await button3.tap()
    let textShadowOptions6: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(textShadowOptions6).$attrs.textShadow.radius, 10)
    assertEqual(JSON.parse(textShadowOptions6).$attrs.textShadow.type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadowOptions6).$attrs.textShadow.color, Color.Blue)
    assertEqual(JSON.parse(textShadowOptions6).$attrs.textShadow.offsetX, 30)
    assertEqual(JSON.parse(textShadowOptions6).$attrs.textShadow.offsetY, 30)
  }, 0)
}
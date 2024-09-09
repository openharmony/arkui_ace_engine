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
import {
  assertEqual,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function textTimerTextShadowTest() {
  /*
 * TextTimer组件 TextShadowOptions属性
 * 找到画面id为textTimerTextShadowOptions1，textTimerTextShadowOptions2，textTimerTextShadowOptions3、 textTimerTextShadowOptions4的TextTimer组件
 * 找到画面文本为TextTimerTextShadowOptions1，TextTimerTextShadowOptions2的Button组件
 * 获取textTimer1的TextShadowOptions属性数组第0位的radius参数与期待值$r("app.integer.text_timer_radius")比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的type参数与期待值ShadowType.BLUR比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的color参数与期待值"#FF0000"比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的offsetX参数与期待值$r("app.integer.text_timer_offsetX1")比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的offsetY参数与期待值$r("app.integer.text_timer_offsetY1")比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的radius参数与期待值$r("app.integer.text_timer_radius")比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的type参数与期待值ShadowType.BLUR比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的color参数与期待值"#0000FF"比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的offsetX参数与期待值$r("app.integer.text_timer_offsetX2")比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的offsetY参数与期待值$r("app.integer.text_timer_offsetY2")比对
 * 点击button1，变更textTimer1的TextShadowOptions属性值为[{radius: 10,type: ShadowType.COLOR,color: Color.Red,offsetX: 10,offsetY: 10},
 * {radius: 10,type: ShadowType.COLOR,color: Color.Yellow,offsetX: 30,offsetY: 30}]
 * 获取textTimer1的TextShadowOptions属性数组第0位的radius参数与期待值10比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的type参数与期待值ShadowType.COLOR比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的color参数与期待值Color.Red比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的offsetX参数与期待值10比对
 * 获取textTimer1的TextShadowOptions属性数组第0位的offsetY参数与期待值10比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的radius参数与期待值10比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的type参数与期待值ShadowType.COLOR比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的color参数与期待值Color.Yellow比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的offsetX参数与期待值30比对
 * 获取textTimer1的TextShadowOptions属性数组第1位的offsetY参数与期待值30比对
 * 获取textTimer2的TextShadowOptions属性数组第0位的radius参数与期待值10比对
 * 获取textTimer2的TextShadowOptions属性数组第0位的type参数与期待值ShadowType.COLOR比对
 * 获取textTimer2的TextShadowOptions属性数组第0位的color参数与期待值Color.Red比对
 * 获取textTimer2的TextShadowOptions属性数组第0位的offsetX参数与期待值10比对
 * 获取textTimer2的TextShadowOptions属性数组第0位的offsetY参数与期待值10比对
 * 获取textTimer2的TextShadowOptions属性数组第1位的radius参数与期待值10比对
 * 获取textTimer2的TextShadowOptions属性数组第1位的type参数与期待值ShadowType.COLOR比对
 * 获取textTimer2的TextShadowOptions属性数组第1位的color参数与期待值Color.Yellow比对
 * 获取textTimer2的TextShadowOptions属性数组第1位的offsetX参数与期待值30比对
 * 获取textTimer2的TextShadowOptions属性数组第1位的offsetY参数与期待值30比对
 * 获取textTimer3的TextShadowOptions属性的radius参数与期待值$r("app.integer.text_timer_radius")比对
 * 获取textTimer3的TextShadowOptions属性的type参数与期待值ShadowType.BLUR比对
 * 获取textTimer3的TextShadowOptions属性的color参数与期待值"#00FF00"比对
 * 获取textTimer3的TextShadowOptions属性的offsetX参数与期待值$r("app.integer.text_timer_offsetX1")比对
 * 获取textTimer3的TextShadowOptions属性的offsetY参数与期待值$r("app.integer.text_timer_offsetY1")比对
 * 点击button2，变更textTimer3的TextShadowOptions属性值为{radius: 10,type: ShadowType.COLOR,color: Color.Blue,offsetX: 30,offsetY: 30}
 * 获取textTimer3的TextShadowOptions属性的radius参数与期待值10比对
 * 获取textTimer3的TextShadowOptions属性的type参数与期待值ShadowType.COLOR比对
 * 获取textTimer3的TextShadowOptions属性的color参数与期待值Color.Blue比对
 * 获取textTimer3的TextShadowOptions属性的offsetX参数与期待值30比对
 * 获取textTimer3的TextShadowOptions属性的offsetY参数与期待值30比对
 * 获取textTimer4的TextShadowOptions属性的radius参数与期待值10比对
 * 获取textTimer4的TextShadowOptions属性的type参数与期待值ShadowType.COLOR比对
 * 获取textTimer4的TextShadowOptions属性的color参数与期待值$r("app.color.text_timer_color1")比对
 * 获取textTimer4的TextShadowOptions属性的offsetX参数与期待值50比对
 * 获取textTimer4的TextShadowOptions属性的offsetY参数与期待值50比对
 */
  defineTest('textTimerTextShadowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textTimerTextShadowTestDemo running')
    let driver: Tester = Tester.create()
    let textTimer1: Component = await driver.findComponent(Matcher.create().id('textTimerTextShadow1').enabled(true))
    let textTimer2: Component = await driver.findComponent(Matcher.create().id('textTimerTextShadow2').enabled(true))
    let textTimer3: Component = await driver.findComponent(Matcher.create().id('textTimerTextShadow3').enabled(true))
    let textTimer4: Component = await driver.findComponent(Matcher.create().id('textTimerTextShadow4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextTimerTextShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextTimerTextShadow2').enabled(true))
    let textShadow1: string = await textTimer1.getInspectorInfo()
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[0].radius, $r("app.string.text_timer_radius"))
    assertTrue(JSON.parse(textShadow1).$attrs.textShadow[0].type == ShadowType.BLUR)
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[0].color, "#FFFF0000")
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[0].offsetX, $r("app.string.text_timer_offsetX1"))
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[0].offsetY, $r("app.string.text_timer_offsetY1"))
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[1].radius, $r("app.string.text_timer_radius"))
    assertTrue(JSON.parse(textShadow1).$attrs.textShadow[1].type == ShadowType.BLUR)
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[1].color, "#FF0000FF")
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[1].offsetX, $r("app.string.text_timer_offsetX2"))
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow[1].offsetY, $r("app.string.text_timer_offsetY2"))
    await button1.tap()
    let textShadow2: string = await textTimer1.getInspectorInfo()
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow[0].radius, '10.000000')
    assertTrue(JSON.parse(textShadow2).$attrs.textShadow[0].type == ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow2)
      .$attrs
      .textShadow[0]
      .color
      .toLowerCase(), Color.Red)
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow[0].offsetX, '10.000000')
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow[0].offsetY, '10.000000')
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow[1].radius, '10.000000')
    assertTrue(JSON.parse(textShadow2).$attrs.textShadow[1].type == ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow2)
      .$attrs
      .textShadow[1]
      .color
      .toLowerCase(), Color.Yellow)
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow[1].offsetX, '30.000000')
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow[1].offsetY, '30.000000')
    let textShadow3: string = await textTimer2.getInspectorInfo()
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[0].radius, '10.000000')
    assertTrue(JSON.parse(textShadow3).$attrs.textShadow[0].type == ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[0].color, $r("app.color.text_timer_color1"))
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[0].offsetX, '10.000000')
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[0].offsetY, '10.000000')
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[1].radius, '10.000000')
    assertTrue(JSON.parse(textShadow3).$attrs.textShadow[1].type == ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[1].color, $r("app.color.text_timer_color2"))
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[1].offsetX, '30.000000')
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow[1].offsetY, '30.000000')
    let textShadow4: string = await textTimer3.getInspectorInfo()
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.radius, $r("app.string.text_timer_radius"))
    assertTrue(JSON.parse(textShadow4).$attrs.textShadow.type == ShadowType.BLUR)
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.color, "#FF00FF00")
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.offsetX, $r("app.string.text_timer_offsetX1"))
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.offsetY, $r("app.string.text_timer_offsetY1"))
    await button2.tap()
    let textShadow5: string = await textTimer3.getInspectorInfo()
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.radius, '10.000000')
    assertTrue(JSON.parse(textShadow5).$attrs.textShadow.type == ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow5)
      .$attrs
      .textShadow
      .color
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.offsetX, '30.000000')
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.offsetY, '30.000000')
    let textShadow6: string = await textTimer4.getInspectorInfo()
    assertEqual(JSON.parse(textShadow6).$attrs.textShadow.radius, '10.000000')
    assertTrue(JSON.parse(textShadow6).$attrs.textShadow.type == ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow6).$attrs.textShadow.color, $r("app.color.text_timer_color1"))
    assertEqual(JSON.parse(textShadow6).$attrs.textShadow.offsetX, '50.000000')
    assertEqual(JSON.parse(textShadow6).$attrs.textShadow.offsetY, '50.000000')
  }, 0)
}
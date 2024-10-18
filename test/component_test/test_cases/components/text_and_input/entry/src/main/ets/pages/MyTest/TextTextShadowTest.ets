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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function textTextShadowTest() {
  /*
* Text组件 TextShadow属性
* 找到画面id为textTextShadow1,textTextShadow2,textTextShadow3的text1,text2,text3组件
* 找到画面文本为TextTextShadow1,TextTextShadow2的Button组件
* 获取text1的TextShadow属性TextShadow.textShadow.radius与期待值[$r('app.integer.number'),$r('app.integer.number')]比对
* 获取text1的TextShadow属性TextShadow.textShadow.type与期待值[ShadowType.BLUR,ShadowType.BLUR]比对
* 获取text1的TextShadow属性TextShadow.textShadow.color与期待值[$r('sys.color.ohos_id_color_text_tertiary'),"#FF4500"]比对
* 获取text1的TextShadow属性TextShadow.textShadow.offsetX与期待值[30,$r('app.integer.offset_radius2')]比对
* 获取text1的TextShadow属性TextShadow.textShadow.offsetY与期待值[30,$r('app.integer.offset_radius2')]比对
* 点击button1，变更text1的TextShadow属性TextShadow.textShadow.radius值为[10,30]
* 变更text1的TextShadow属性TextShadow.textShadow.type值为[ShadowType.COLOR,ShadowType.COLOR]
* 变更text1的TextShadow属性TextShadow.textShadow.color值为[Color.Red,ColoringStrategy.PRIMARY]
* 变更text1的TextShadow属性TextShadow.textShadow.offsetX值为[10,30]
* 变更text1的TextShadow属性TextShadow.textShadow.offsetY值为[10,30]
* 获取text1的TextShadow属性TextShadow.textShadow.radius与期待值[10,30]比对
* 获取text1的TextShadow属性TextShadow.textShadow.type与期待值[ShadowType.COLOR,ShadowType.COLOR]比对
* 获取text1的TextShadow属性TextShadow.textShadow.color与期待值[Color.Red,ColoringStrategy.PRIMARY]比对
* 获取text1的TextShadow属性TextShadow.textShadow.offsetX与期待值[10,30]比对
* 获取text1的TextShadow属性TextShadow.textShadow.offsetY与期待值[10,30]比对
* 获取text2的TextShadow属性TextShadow.textShadow.radius与期待值$r('app.integer.number')比对
* 获取text2的TextShadow属性TextShadow.textShadow.type与期待值ShadowType.BLUR比对
* 获取text2的TextShadow属性TextShadow.textShadow.color与期待值0xffffff比对
* 获取text2的TextShadow属性TextShadow.textShadow.offsetX与期待值$r('app.integer.offset_radius1')比对
* 获取text2的TextShadow属性TextShadow.textShadow.offsetY与期待值$r('app.integer.offset_radius1')比对
* 获取text2的TextShadow属性TextShadow.textShadow.fill与期待值true比对
* 点击button2，变更text2的TextShadow属性TextShadow.textShadow.radius值为10
* 变更text2的TextShadow属性TextShadow.textShadow.type值为ShadowType.COLOR
* 变更text2的TextShadow属性TextShadow.textShadow.color值为ColoringStrategy.INVERT
* 变更text2的TextShadow属性TextShadow.textShadow.offsetX值为30
* 变更text2的TextShadow属性TextShadow.textShadow.offsetY值为30
* 变更text2的TextShadow属性TextShadow.textShadow.fill值为false
* 获取text2的TextShadow属性TextShadow.textShadow.radius与期待值10比对
* 获取text2的TextShadow属性TextShadow.textShadow.type与期待值ShadowType.COLOR比对
* 获取text2的TextShadow属性TextShadow.textShadow.color与期待值ColoringStrategy.INVERT比对
* 获取text2的TextShadow属性TextShadow.textShadow.offsetX与期待值30比对
* 获取text2的TextShadow属性TextShadow.textShadow.offsetY与期待值30比对
* 获取text2的TextShadow属性TextShadow.textShadow.fill与期待值false比对
* 获取text3的TextShadow属性TextShadow.textShadow.radius与期待值10比对
* 获取text3的TextShadow属性TextShadow.textShadow.color与期待值ColoringStrategy.AVERAGE比对
*/
  defineTest('textTextShadowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textTextShadowTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textTextShadow1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textTextShadow2').enabled(true))
    let text3: Component = await driver.findComponent(Matcher.create().id('textTextShadow3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextTextShadow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextTextShadow2').enabled(true))

    let textShadow1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow.radius, [$r('app.integer.number'), $r('app.integer.number')])
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow.type, [ShadowType.BLUR, ShadowType.BLUR])
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow.color,
      [$r('sys.color.ohos_id_color_text_tertiary'), "#FF4500"])
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow.offsetX, [30, $r('app.integer.offset_radius2')])
    assertEqual(JSON.parse(textShadow1).$attrs.textShadow.offsetY, [30, $r('app.integer.offset_radius2')])
    let textShadow2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow.radius, $r('app.integer.number'))
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow.type, ShadowType.BLUR)
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow.color, 0xffffff)
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow.offsetX, $r('app.integer.offset_radius1'))
    assertEqual(JSON.parse(textShadow2).$attrs.textShadow.offsetY, $r('app.integer.offset_radius1'))
    assertFalse(JSON.parse(textShadow2).$attrs.textShadow.fill)
    let textShadow3: string = await text3.getInspectorInfo()
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow.radius, 10)
    assertEqual(JSON.parse(textShadow3).$attrs.textShadow.color, ColoringStrategy.AVERAGE)

    await button1.tap()
    let textShadow4: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.radius, [10, 30])
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.type, [ShadowType.COLOR, ShadowType.COLOR])
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.color, [Color.Red, ColoringStrategy.PRIMARY])
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.offsetX, [10, 30])
    assertEqual(JSON.parse(textShadow4).$attrs.textShadow.offsetY, [10, 30])
    await button2.tap()
    let textShadow5: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.radius, 10)
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.type, ShadowType.COLOR)
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.color, ColoringStrategy.INVERT)
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.offsetX, 30)
    assertEqual(JSON.parse(textShadow5).$attrs.textShadow.offsetY, 30)
    assertTrue(JSON.parse(textShadow5).$attrs.textShadow.fill)
  }, 0)
}
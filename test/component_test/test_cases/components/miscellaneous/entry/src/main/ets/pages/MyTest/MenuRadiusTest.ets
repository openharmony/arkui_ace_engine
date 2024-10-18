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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function menuRadiusTest() {
  /*
* Menu组件 Radius属性
* 找到画面id为menuRadius1、 menuRadius2、 menuRadius3、 menuRadius4、 menuRadius5、 menuRadius6的Menu组件
* 找到画面文本为MenuRadius1、 MenuRadius2、 MenuRadius3的Button组件
* 获取menu1的Radius属性值与期待值'30.00px'比对
* 点击button1，变更menu1的Radius属性值为'100vp'
* 获取menu1的Radius属性值与期待值'100.00vp'比对
* 点击button2，变更menu1的Radius属性值为'10fp'
* 获取menu1的Radius属性值与期待值'10.00fp'比对
* 获取menu2的Radius属性值与期待值'30.00lpx'比对
* 获取menu3的Radius属性值与期待值'10%'比对
* 获取menu4的Radius属性值与期待值$r('app.string.length')比对
* 获取menu5的Radius属性值与期待值{ topLeft: "10.00px", topRight: "10.00px", bottomLeft: "10.00px", bottomRight: "10.00px" }比对
* 获取menu6的Radius属性值与期待值{ topLeft: 50, topRight: 50, bottomLeft: 50, bottomRight: 50 }比对
* 点击button3，变更menu6的Radius属性值为{ topLeft: $r('app.string.length'), topRight: $r('app.string.length'),
* bottomLeft: $r('app.string.length'), bottomRight: $r('app.string.length') }
* 获取menu6的Radius属性值与期待值{ topLeft: $r('app.string.length'), topRight: $r('app.string.length'),
* bottomLeft: $r('app.string.length'), bottomRight: $r('app.string.length') }比对
*/
  defineTest('menuRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuRadiusTestDemo running')
    let driver: Tester = Tester.create()
    let menu1: Component = await driver.findComponent(Matcher.create().id('menuRadius1').enabled(true))
    let menu2: Component = await driver.findComponent(Matcher.create().id('menuRadius2').enabled(true))
    let menu3: Component = await driver.findComponent(Matcher.create().id('menuRadius3').enabled(true))
    let menu4: Component = await driver.findComponent(Matcher.create().id('menuRadius4').enabled(true))
    let menu5: Component = await driver.findComponent(Matcher.create().id('menuRadius5').enabled(true))
    let menu6: Component = await driver.findComponent(Matcher.create().id('menuRadius6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuRadius1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuRadius2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('MenuRadius3').enabled(true))

    let radius1: string = await menu1.getInspectorInfo()
    assertFalse(JSON.parse(radius1).$attrs.radius == undefined)
    assertEqual(JSON.parse(radius1).$attrs.radius, '30.00px')
    await button1.tap()
    let radius2: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(radius2).$attrs.radius, '100.00vp')
    await button2.tap()
    let radius3: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(radius3).$attrs.radius, '10.00fp')

    let radius4: string = await menu2.getInspectorInfo()
    assertEqual(JSON.parse(radius4).$attrs.radius, '30.00lpx')

    let radius5: string = await menu3.getInspectorInfo()
    assertEqual(JSON.parse(radius5).$attrs.radius, '10%')

    let radius6: string = await menu4.getInspectorInfo()
    assertEqual(JSON.parse(radius6).$attrs.radius, $r('app.string.length'))

    let radius7: string = await menu5.getInspectorInfo()
    assertEqual(JSON.parse(radius7).$attrs.radius.topLeft, "10.00px")
    assertEqual(JSON.parse(radius7).$attrs.radius.topRight, "10.00px")
    assertEqual(JSON.parse(radius7).$attrs.radius.bottomLeft, "10.00px")
    assertEqual(JSON.parse(radius7).$attrs.radius.bottomRight, "10.00px")

    let radius8: string = await menu6.getInspectorInfo()
    assertEqual(JSON.parse(radius8).$attrs.radius.topLeft, '50')
    assertEqual(JSON.parse(radius8).$attrs.radius.topRight, '50')
    assertEqual(JSON.parse(radius8).$attrs.radius.bottomLeft, '50')
    assertEqual(JSON.parse(radius8).$attrs.radius.bottomRight, '50')
    await button3.tap()
    let radius9: string = await menu6.getInspectorInfo()
    assertEqual(JSON.parse(radius9).$attrs.radius.topLeft, $r('app.string.length'))
    assertEqual(JSON.parse(radius9).$attrs.radius.topRight, $r('app.string.length'))
    assertEqual(JSON.parse(radius9).$attrs.radius.bottomLeft, $r('app.string.length'))
    assertEqual(JSON.parse(radius9).$attrs.radius.bottomRight, $r('app.string.length'))
  }, 0)
}
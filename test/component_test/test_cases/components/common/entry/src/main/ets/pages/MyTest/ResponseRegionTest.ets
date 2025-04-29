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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function responseRegionTest() {
  /*
  * 使用组件 button ResponseRegion属性
  * 找到画面id为buttonResponseRegion1，buttonResponseRegion2，buttonResponseRegion3的Button组件
  * 找到画面文本为ButtonResponseRegion的Button组件
  * 获取buttonResponseRegion1的ResponseRegion属性与期待值{ x: 0.00vp, y: 0.00vp, width: 50.00vp, height: 100.00vp }比对
  * 获取buttonResponseRegion2的ResponseRegion属性与期待值[ { x: '100.00vp', y: 0.00vp, width: '50.00vp', height: '100.00vp' },{ x: 0.00vp, y: 0.00vp, width: '50.00vp', height: '100.00vp' } ]比对
  * 获取buttonResponseRegion3的ResponseRegion属性与期待值 { x: '0px', y: '0px', width: '50px',  height: '100px' }比对
  * 点击button，变更buttonResponseRegion3的ResponseRegion属性值为 { x: $r('app.string.commonPosition_length'),   y: $r('app.string.commonPosition_length'),   width: $r('app.string.commonImage_width'),   height: $r('app.string.commonImage_height') }
  * 获取buttonResponseRegion3的ResponseRegion属性与期待值  { x: $r('app.string.commonPosition_length'),   y: $r('app.string.commonPosition_length'),    width: $r('app.string.commonImage_width'),  height: $r('app.string.commonImage_height') }比对
  */
  defineTest('responseRegionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('responseRegionTestDemo running')
    let driver: Tester = Tester.create()
    let buttonResponseRegion1: Component =
      await driver.findComponent(Matcher.create().id('buttonResponseRegion1').enabled(true))
    let buttonResponseRegion2: Component =
      await driver.findComponent(Matcher.create().id('buttonResponseRegion2').enabled(true))
    let buttonResponseRegion3: Component =
      await driver.findComponent(Matcher.create().id('buttonResponseRegion3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonResponseRegion').enabled(true))

    let responseRegion1: string = await buttonResponseRegion1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(responseRegion1).$attrs.responseRegion).x, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion1).$attrs.responseRegion).y, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion1).$attrs.responseRegion).width, '50.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion1).$attrs.responseRegion).height, '100.00vp')

    let responseRegion2: string = await buttonResponseRegion2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[0]).x, '100.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[0]).y, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[0]).width, '50.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[0]).height, '100.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[1]).x, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[1]).y, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[1]).width, '50.00vp')
    assertEqual(JSON.parse(JSON.parse(responseRegion2).$attrs.responseRegion[1]).height, '100.00vp')

    await button.tap()
    let responseRegion4: string = await buttonResponseRegion3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(responseRegion4).$attrs.responseRegion).x, $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(responseRegion4).$attrs.responseRegion).y, $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(responseRegion4).$attrs.responseRegion).width, $r('app.string.commonImage_width'))
    assertEqual(JSON.parse(JSON.parse(responseRegion4).$attrs.responseRegion).height,
      $r('app.string.commonImage_width'))
  }, 0)
}
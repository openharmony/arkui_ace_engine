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

export default async function actionSheetOffsetTest() {
  /*
* ActionSheet组件 Offset对象
* 找到画面id为actionSheetOffset1,actionSheetOffset2的ActionSheet组件
* 找到画面文本为ActionSheetOffset的Button组件
* 获取actionSheetOffset1的Offset对象与期待值{dx:$r('app.string.actionSheet_offset_dx'),dy:$r('app.string.actionSheet_offset_dy')}比对
* 获取actionSheetOffset2的Offset对象与期待值{dx:2,dy:-20}比对
* 点击button，变更actionSheetOffset2，的对象值{dx:"8px",dy:"-80px"}
* 获取actionSheetOffset2的Offset对象与期待值{dx:"8px",dy:"-80px"}比对

*/
  defineTest('actionSheetOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetOffsetTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetOffsetTest1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ActionSheetOffsetTest2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetOffset1').enabled(true))
    await button1.tap()
    let actionSheetOffset1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let offset1: string = await actionSheetOffset1.getInspectorInfo()
    assertEqual(String(JSON.parse(offset1).$attrs.offset.dX), $r('app.string.actionSheet_offset_dx'))
    assertEqual(String(JSON.parse(offset1).$attrs.offset.dY), $r('app.string.actionSheet_offset_dy'))
    await driver.tap(1, 1)
    await button2.tap()
    let actionSheetOffset2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let offset2: string = await actionSheetOffset2.getInspectorInfo()
    assertEqual(JSON.parse(offset2).$attrs.offset.dX, 2)
    assertEqual(JSON.parse(offset2).$attrs.offset.dY, -20)
    await driver.tap(1, 1)
    await button.tap()
    await button2.tap()
    let actionSheetOffset3: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let offset3: string = await actionSheetOffset3.getInspectorInfo()
    assertEqual(JSON.parse(offset3).$attrs.offset.dX, 8)
    assertEqual(JSON.parse(offset3).$attrs.offset.dY, -80)
    await driver.tap(1, 1)
  }, 0)
}
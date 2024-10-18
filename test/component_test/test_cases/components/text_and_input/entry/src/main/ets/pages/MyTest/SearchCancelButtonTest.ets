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

/*
* Search组件 CancelButton属性
* 找到画面id为searchCancelButton1,searchCancelButton2的Search组件
* 找到画面文本为SearchCancelButton1,SearchCancelButton2的Button组件
* 获取search1的CancelButton属性CancelButton.style与期待值CancelButtonStyle.CONSTANT比对
* 获取search1的CancelButton属性CancelButton.icon.size与期待值'50px'比对
* 获取search1的CancelButton属性CancelButton.icon.src与期待值"../../../resources/base/media/icon.png"比对
* 获取search1的CancelButton属性CancelButton.icon.color与期待值0xffff0000比对
* 点击button1，变更search1的CancelButton属性CancelButton.style值为CancelButtonStyle.INVISIBLE
* 点击button1，变更search1的CancelButton属性值为{ size:100, src: $r('app.media.startIcon'), color: Color.Blue}
* 获取search1的CancelButton属性CancelButton.style与期待值CancelButtonStyle.INVISIBLE比对
* 获取search1的CancelButton属性CancelButton.icon.size与期待值100比对
* 获取search1的CancelButton属性CancelButton.icon.src与期待值$r('app.media.startIcon')比对
* 获取search1的CancelButton属性CancelButton.icon.color与期待值Color.Blue比对
* 点击button2，变更search1的CancelButton属性CancelButton.style值为CancelButtonStyle.INVISIBLE
* 点击button2，变更search1的CancelButton属性CancelButton.icon.size值为$r('app.string.length')
* 点击button2，变更search1的CancelButton属性CancelButton.icon.color值为'#ffffff'
* 获取search1的CancelButton属性CancelButton.style与期待值CancelButtonStyle.CONSTANT比对
* 获取search1的CancelButton属性CancelButton.icon.size与期待值$r('app.string.length')比对
* 获取search1的CancelButton属性CancelButton.icon.color与期待值'#ffffff'比对
* 获取search2的CancelButton属性CancelButton.style与期待值CancelButtonStyle.INPUT比对
* 获取search2的CancelButton属性CancelButton.icon.color与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
export default async function searchCancelButtonTest() {
  defineTest('searchCancelButtonTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchCancelButtonTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchCancelButton1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchCancelButton2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchCancelButton1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchCancelButton2').enabled(true))

    let cancelButton1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(cancelButton1).$attrs.cancelButton.style, 'CancelButtonStyle.CONSTANT')
    assertEqual(JSON.parse(cancelButton1)
      .$attrs
      .cancelButton
      .icon
      .size, '50.00px')
    assertEqual(JSON.parse(cancelButton1)
      .$attrs
      .cancelButton
      .icon
      .src, "../../../resources/base/media/icon.png")
    assertEqual(JSON.parse(cancelButton1)
      .$attrs
      .cancelButton
      .icon
      .color, '#FFFF0000')
    let cancelButton2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(cancelButton2).$attrs.cancelButton.style, 'CancelButtonStyle.CONSTANT')
    assertEqual(JSON.parse(cancelButton2)
      .$attrs
      .cancelButton
      .icon
      .color, $r('sys.color.ohos_id_color_text_hyperlink'))
    await button1.tap()
    let cancelButton3: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(cancelButton3).$attrs.cancelButton.style, CancelButtonStyle.INPUT)
    assertEqual(JSON.parse(cancelButton3)
      .$attrs
      .cancelButton
      .icon
      .size, '100.00vp')
    assertEqual(JSON.parse(cancelButton3)
      .$attrs
      .cancelButton
      .icon
      .src, $r('app.media.startIcon'))
    assertEqual(JSON.parse(cancelButton3)
      .$attrs
      .cancelButton
      .icon
      .color
      .toLowerCase(), Color.Blue)
    await button2.tap()
    let cancelButton4: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(cancelButton4).$attrs.cancelButton.style, CancelButtonStyle.INVISIBLE)
    assertEqual(JSON.parse(cancelButton4)
      .$attrs
      .cancelButton
      .icon
      .size, $r('app.string.length'))
    assertEqual(JSON.parse(cancelButton4)
      .$attrs
      .cancelButton
      .icon
      .color, '#ffffff')
  }, 0)
}
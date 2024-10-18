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
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function textInputCancelButtonTest() {
  /*
   * TextInput组件 CancelButton属性
   * 找到画面id为textInputCancelButton1,textInputCancelButton2的TextInput组件
   * 找到画面文本为TextInputCancelButton1,TextInputCancelButton2的Button组件
   * 获取textInput1的CancelButton属性CancelButton.style与期待值2比对
   * 获取textInput1的CancelButton属性CancelButton.icon.size与期待值'45.00vp'比对
   * 获取textInput1的CancelButton属性CancelButton.icon.color与期待值'#FF0000FF'比对
   * 获取textInput1的CancelButton属性CancelButton.icon.src与期待值$r('app.media.startIcon')比对
   * 获取textInput2的CancelButton属性CancelButton.style与期待值0比对
   * 获取textInput2的CancelButton属性CancelButton.icon.size与期待值'50.00px'比对
   * 获取textInput2的CancelButton属性CancelButton.icon.color与期待值'#FFFF0000'比对
   * 获取textInput2的CancelButton属性CancelButton.icon.src与期待值'../../../resources/base/media/icon.png'比对
   * 点击button1，变更textInput2的CancelButton属性CancelButton.style值为CancelButtonStyle.INVISIBLE
   * 变更textInput2的CancelButton属性CancelButton.icon.size值为$r('app.string.vp_length')
   * 变更textInput2的CancelButton属性CancelButton.icon.color值为'rgb(235,50,122)'
   * 获取textInput2的CancelButton属性CancelButton.style与期待值1比对
   * 获取textInput2的CancelButton属性CancelButton.icon.size与期待值$r('app.string.vp_length')比对
   * 获取textInput2的CancelButton属性CancelButton.icon.color与期待值'#FFEB327A'比对
   * 点击button2，变更textInput2的CancelButton属性CancelButton.style值为CancelButtonStyle.CONSTANT
   * 变更textInput2的CancelButton属性CancelButton.icon.color值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取textInput2的CancelButton属性CancelButton.style与期待值0比对
   * 获取textInput2的CancelButton属性CancelButton.icon.color与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('textInputCancelButtonTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputCancelButtonTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputCancelButton1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputCancelButton2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputCancelButton1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputCancelButton2').enabled(true))

    let cancelButton1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(cancelButton1).$attrs.cancelButton).style, 2)
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton1).$attrs.cancelButton).icon).size, '45.00vp')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton1).$attrs.cancelButton).icon).color, '#FF0000FF')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton1).$attrs.cancelButton).icon).src,
      $r('app.media.startIcon'))
    let cancelButton2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(cancelButton2).$attrs.cancelButton).style, 0)
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton2).$attrs.cancelButton).icon).size, '50.00px')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton2).$attrs.cancelButton).icon).color, '#FFFF0000')
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton2).$attrs.cancelButton).icon).src,
      '../../../resources/base/media/icon.png')

    await button1.tap()
    let cancelButton3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(cancelButton3).$attrs.cancelButton).style, 1)
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton3).$attrs.cancelButton).icon).size,
      $r('app.string.vp_length'))
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton3).$attrs.cancelButton).icon).color, '#FFEB327A')

    await button2.tap()
    let cancelButton4: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(cancelButton4).$attrs.cancelButton).style, 0)
    assertEqual(JSON.parse(JSON.parse(JSON.parse(cancelButton4).$attrs.cancelButton).icon).color,
      $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}
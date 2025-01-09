import { Component, Driver, ON } from '@kit.TestKit';
import { expect } from '@ohos/hypium';
import { curves } from '@kit.ArkUI';
import { Point } from '@ohos.UiTest';

const driver = Driver.create();
const TAG = 'utils'

export class KeyStruct {
  public key: string;
  public type: JsonType;

  constructor(key: string, type: JsonType) {
    this.key = key;
    this.type = type;
  }
}

export enum JsonType {
  value,
  obj,
  array
}

export enum ToggleClick {
  Open,
  Close,
}

export enum Slide {
  start = 1,
  end = 0,
}

export interface toggleClickType {
  toggleClickType: ToggleClick
  toggleClickObj: number
}

export interface radioOperateType {
  radioClickObj: number
  toggleClick?: toggleClickType
  id?: string
  arr?: Array<KeyStruct>
  assertEqual?: string
}

export interface sliderOperateType {
  slideStar: Slide,
  toggleClick?: toggleClickType
  id?: string,
  arr?: Array<KeyStruct>
  assertEqual?: string
}

export interface buttonOperateType {
  buttonClickObj: number,
  toggleClick?: toggleClickType
  id?: string
  arr?: Array<KeyStruct>
  assertEqual?: string
}

// 通过id验证有没有这个组件 有的话点击一下
export async function checkButtonAndClickWithID(text: string) {
  let atom = text;
  await driver.assertComponentExist(ON.id(atom));
  let button = await driver.findComponent(ON.id(atom));
  await button.click();
  await driver.delayMs(1000);
  console.info(TAG, atom);
}

// 向下滑动一个Block的距离
export async function swipeColumn() {
  let toggle:Component[] = await driver.findComponents(ON.type('Toggle'))
  let width:Point = await toggle[0].getBoundsCenter()
  let width2:Point = await toggle[1].getBoundsCenter()

  let scroller: Scroller | undefined = AppStorage.get('scroller')

  let curve = curves.interpolatingSpring(10, 1, 228, 30)

  if (scroller) {
    const yOffset: number = scroller.currentOffset().yOffset;
    scroller.scrollTo({
      xOffset: 0,
      yOffset: yOffset + px2vp(width2.y - width.y),
      animation: { duration: 1000, curve: curve }
    })
  }


  await driver.delayMs(1000);
}

// 获取组件属性具体值
export function getJson(arr: Array<KeyStruct> | undefined, json: string) {
  if (!arr) {
    return undefined
  }

  let obj: object = JSON.parse(json);
  let lastType = JsonType.obj;

  for (let i = 0; i < arr.length; i++) {
    const keyStruct: KeyStruct = arr[i];
    try {
      if (JsonType.array == lastType) {
        obj = obj[parseInt(keyStruct.key)];
      } else {
        obj = obj[keyStruct.key];
      }
    } catch (e) {
      console.error(e);
      return undefined;
    }
    lastType = keyStruct.type;
  }
  return obj;

}

// 根据参数点击RadioBlock项
export async function radioClick(radioOperate: radioOperateType) {

  if (radioOperate.toggleClick?.toggleClickType != undefined &&
    radioOperate.toggleClick?.toggleClickType == ToggleClick.Open) {

    let toggle:Component[] = await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')))
    await toggle[radioOperate.toggleClick.toggleClickObj].click()
    await driver.delayMs(1000);

  }

  if (radioOperate.radioClickObj != undefined) {
    let radio:Component[] = await driver.findComponents(ON.type('Radio').within(ON.type('Scroll')).clickable(true))
    await radio[radioOperate.radioClickObj].click(); // 等待点击操作完成
    await driver.delayMs(1000);
  }

  if (radioOperate.id) {

    let idValue = getInspectorByKey(radioOperate.id)

    console.log(idValue)

    let result = getJson(radioOperate.arr, idValue)

    expect(result).assertEqual(radioOperate.assertEqual);

    console.log(TAG, result, 'expect', radioOperate.assertEqual)

  }

  if (radioOperate.toggleClick?.toggleClickType != undefined &&
    radioOperate.toggleClick?.toggleClickType == ToggleClick.Close) {
    let toggle:Component[] = await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')))
    await toggle[radioOperate.toggleClick.toggleClickObj].click()
    await driver.delayMs(1000);
  }

}

// 根据参数滑动SliderBlock
export async function sliderDrag(sliderOperate: sliderOperateType) {

  if (sliderOperate.toggleClick?.toggleClickType != undefined &&
    sliderOperate.toggleClick?.toggleClickType == ToggleClick.Open) {
    let toggle:Component[] = await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')))
    await toggle[sliderOperate.toggleClick.toggleClickObj].click()
    await driver.delayMs(1000);
  }

  let slider:Component = await driver.findComponent(ON.type('Slider').within(ON.type('Scroll')).scrollable(true))
  let point = await slider.getBoundsCenter();
  let rect = await slider.getBounds();

  if (sliderOperate.slideStar) {
    await driver.drag(rect.left, point.y, rect.right, point.y)
    await driver.delayMs(1000);
  } else {
    await driver.drag(rect.right, point.y, rect.left, point.y)
    await driver.delayMs(1000);
  }

  if (sliderOperate.id) {
    let idValue = getInspectorByKey(sliderOperate.id)

    let result = getJson(sliderOperate.arr, idValue)

    expect(result).assertEqual(sliderOperate.assertEqual);
    console.log(TAG, result, 'expect', sliderOperate.assertEqual)
  }

  if (sliderOperate.toggleClick?.toggleClickType != undefined &&
    sliderOperate.toggleClick.toggleClickType == ToggleClick.Close) {
    let toggle:Component[] = await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')))
    await toggle[sliderOperate.toggleClick.toggleClickObj].click()
    await driver.delayMs(1000);
  }

}

// 根据参数点击ButtonBlock项
export async function buttonClick(buttonOperate: buttonOperateType) {

  if (buttonOperate.toggleClick?.toggleClickType != undefined &&
    buttonOperate.toggleClick?.toggleClickType == ToggleClick.Open) {
    let toggle:Component[] = await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')))
    await toggle[buttonOperate.toggleClick.toggleClickObj].click()
    await driver.delayMs(1000);
  }
  let button:Component[] = await driver.findComponents(ON.type('Button').within(ON.type('Scroll')).clickable(true))

  await button[buttonOperate.buttonClickObj].click()
  await driver.delayMs(1000);

  if (buttonOperate.id) {
    let idValue = getInspectorByKey(buttonOperate.id)

    let result = getJson(buttonOperate.arr, idValue)

    expect(result).assertEqual(buttonOperate.assertEqual);

    console.log(TAG, result, 'expect', buttonOperate.assertEqual)
  }

  if (buttonOperate.toggleClick?.toggleClickType != undefined &&
    buttonOperate.toggleClick?.toggleClickType == ToggleClick.Close) {
    let toggle:Component[] = await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')))
    await toggle[buttonOperate.toggleClick.toggleClickObj].click()
    await driver.delayMs(1000);
  }

}

import { Component, Driver, ON } from '@kit.TestKit';
import { expect } from '@ohos/hypium';
import { componentUtils, curves } from '@kit.ArkUI';
import { MatchPattern, On, Point, Rect } from '@ohos.UiTest';

const driver = Driver.create();
const TAG = 'Test utils'

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

export enum Direction {
  width = 0,
  height = 1
}

export interface toggleClickTypes {
  toggleClickType?: ToggleClick
  toggleClickObj?: string
}

export interface radioOperateType {
  radioClickObj: number | string
  toggleClick?: toggleClickTypes
  id?: string
  arr?: Array<KeyStruct>
  assertEqual?: string | number | boolean | Array<number> | Array<string>
}

export interface sliderOperateType {
  slideStar: Slide,
  slideDragObj?: number
  toggleClick?: toggleClickTypes
  id?: string,
  arr?: Array<KeyStruct>
  assertEqual?: string | number | boolean
}

export interface buttonOperateType {
  buttonClickObj: number,
  toggleClick?: toggleClickTypes
  id?: string
  arr?: Array<KeyStruct>
  assertEqual?: string | number | boolean
}

// 通过id验证有没有这个组件 有的话点击一下
export async function checkButtonAndClickWithID(text: string) {
  let atom = text;
  await driver.assertComponentExist(ON.id(atom));
  let button = await driver.findComponent(ON.id(atom));
  await button.click();
  await driver.delayMs(1500);
  console.info(TAG, atom);
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
export async function radioClick(radioOperate: radioOperateType, blockStr?: string, compText?: string,
  listText?: string) {
  await getToggle(ToggleClick.Open, radioOperate.toggleClick?.toggleClickObj)
  if (radioOperate.radioClickObj != undefined) {
    if (typeof radioOperate.radioClickObj === 'string') {
      await searchRadio(radioOperate.radioClickObj)
    } else {
      let radio: Component[] =
        await driver.findComponents(ON.type('Radio').within(ON.type('Scroll')).clickable(true))
      await radio[radioOperate.radioClickObj].click(); // 等待点击操作完成
      await driver.delayMs(1500);
    }
  }
  if (radioOperate.id) {
    let idValue = getInspectorByKey(radioOperate.id)
    console.log(idValue)
    let result = getJson(radioOperate.arr, idValue)
    expect(JSON.stringify(result)).assertEqual(JSON.stringify(radioOperate.assertEqual));
    console.log(TAG, result, 'expect', radioOperate.assertEqual)
  }
  if (radioOperate.toggleClick != undefined &&
    radioOperate.toggleClick.toggleClickType == ToggleClick.Close) {
    if (typeof radioOperate.radioClickObj === 'string' && blockStr && compText && listText) {
      await searchParentBlock(blockStr, false, compText, listText)
    } else {
      await getToggle(radioOperate.toggleClick.toggleClickType, radioOperate.toggleClick.toggleClickObj)
    }
  }
}


// 根据参数滑动SliderBlock
export async function sliderDrag(sliderOperate: sliderOperateType) {


  await getToggle(ToggleClick.Open, sliderOperate.toggleClick?.toggleClickObj)

  let slider: Component

  if (sliderOperate.slideDragObj) {
    let sliders = await driver.findComponents(ON.type('Slider').within(ON.type('Scroll')).scrollable(true))
    slider = sliders[sliderOperate.slideDragObj]
  } else {
    slider = await driver.findComponent(ON.type('Slider').within(ON.type('Scroll')).scrollable(true))
  }

  let point = await slider.getBoundsCenter();
  let rect = await slider.getBounds();

  if (sliderOperate.slideStar) {
    await driver.drag(rect.left, point.y, rect.right, point.y)
    await driver.delayMs(1500);
  } else {
    await driver.drag(rect.right, point.y, rect.left, point.y)
    await driver.delayMs(1500);
  }

  if (sliderOperate.id) {
    let idValue = getInspectorByKey(sliderOperate.id)
    console.log(TAG, idValue)
    let result = getJson(sliderOperate.arr, idValue)
    console.log(TAG, result, 'expect', sliderOperate.assertEqual)
    expect(result).assertEqual(sliderOperate.assertEqual);

  }
  if (sliderOperate.toggleClick != undefined &&
    sliderOperate.toggleClick.toggleClickType == ToggleClick.Close) {
    await getToggle(sliderOperate.toggleClick.toggleClickType, sliderOperate.toggleClick.toggleClickObj)
  }
}

// 根据参数点击ButtonBlock项
export async function buttonClick(buttonOperate: buttonOperateType) {
  await getToggle(ToggleClick.Open, buttonOperate.toggleClick?.toggleClickObj)
  let button: Component[] =
    await driver.findComponents(ON.type('Button').within(ON.id('scroll')).clickable(true))

  await button[buttonOperate.buttonClickObj].click()
  await driver.delayMs(1500);

  if (buttonOperate.id) {
    let idValue = getInspectorByKey(buttonOperate.id)

    let result = getJson(buttonOperate.arr, idValue)

    expect(result).assertEqual(buttonOperate.assertEqual);


    console.log(TAG, result, 'expect', buttonOperate.assertEqual)
  }

  if (buttonOperate.toggleClick != undefined &&
    buttonOperate.toggleClick.toggleClickType == ToggleClick.Close) {
    await getToggle(buttonOperate.toggleClick.toggleClickType, buttonOperate.toggleClick.toggleClickObj)
  }

}

/*滚动*/
export async function scroll(distance: number) {
  let scroller: Scroller | undefined = AppStorage.get('scroller')
  let curve = curves.interpolatingSpring(10, 1, 228, 30)
  if (scroller) {
    const yOffset: number = scroller.currentOffset().yOffset;
    scroller.scrollTo({
      xOffset: 0,
      yOffset: yOffset + px2vp(distance),
      animation: { duration: 1000, curve: curve }
    })
    return true;
  }
  return false;
}

//通过id获取组件宽高
export function getCompSize(id: string, direction: Direction): number {
  let size = 0
  if (direction == Direction.width) {
    size = componentUtils.getRectangleById(id).size.width;
  }
  if (direction == Direction.height) {
    size = componentUtils.getRectangleById(id).size.height;
  }
  return size;
}

//category为参数列表or基本属性，compText为目标文本， listText为可选参数（ListGroup标题）
export async function Search(category: string, compText: string, listText?: string) {
  let selection: string | undefined = AppStorage.get('selection')
  let titleRect: Rect
  if (category == '参数列表') {
    let scrolls: Component = await driver.findComponent(ON.id('scroll'));
    let title: Component = await scrolls.scrollSearch(ON.text(compText));
    titleRect = await title.getBounds();
    if (title) {
      scroll(titleRect.top - 678)
    }
  } else {
    let textSearch: Component = await driver.findComponent(ON.text('基础属性'))
    await driver.delayMs(1500)
    await textSearch.click()
    let scrolls: Component = await driver.findComponent(ON.id('scroll'));
    if (listText) {
      if (selection != listText) {
        let titles: Component = await scrolls.scrollSearch(ON.text(listText))
        await titles.click()
        await scrolls.scrollToTop();
      }
      let title: Component = await scrolls.scrollSearch(ON.text(compText))
      if (title) {
        titleRect = await title.getBounds();
        scroll(titleRect.top - 678)
      }
    } else {
      let title: Component = await scrolls.scrollSearch(ON.text(compText))
      titleRect = await title.getBounds();
      if (title) {
        scroll(titleRect.top - 678)
      }
    }
  }
}

//LastCompText为可选参数，当scroller触底之后LastCompText为你要控制toggle的前面一个toggle文本
export async function getToggle(isClose: ToggleClick = ToggleClick.Open, lastCompText?: string) {
  let toggle: Component =
    await driver.findComponent(lastCompText ?
    ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text(lastCompText)) :
    ON.type('Toggle').within(ON.type('Scroll')));
  if (await toggle.isChecked() === (isClose === ToggleClick.Close)) {
    await toggle.click();
    await driver.delayMs(1500)
  }
}
export async function titleSearch(category: string, compText: string, listText?: string) {
  let title = await driver.findComponent(ON.text(compText))
  await driver.delayMs(1500)
  if (title) {
    let titleRect = await title.getBounds();
    await scroll(titleRect.top - 678)
  } else {
    await Search(category, compText, listText)
  }
}


export async function searchRadio(radioName: string) {
  let isSearch: boolean = true
  while (isSearch) {
    let text = await driver.findComponent(ON.text(radioName).within(ON.type('Scroll')))
    if (text) {
      let radios: Component[] = await driver.findComponents(ON.type('Radio').within(ON.type('Scroll')).clickable(true))
      let texts: Component[] = await driver.findComponents(ON.type('Text').within(ON.type('Scroll')))
      for (let i = 0; i < texts.length; i++) {
        if (await texts[i].getText() === radioName) {
          await radios[i].click()
          await driver.delayMs(1500)
          break
        }
      }
      break
    } else {
      scroll(getCompSize('scroll', Direction.height) + 18)
    }
  }
}

// searchStr 搜索关键字   clickBool 想要的状态  category  Search的category
export async function searchParentBlock(searchStr: string, clickBool: boolean = true, category: string = '基础属性',
  listText?: string) {
  if (listText) {
    await Search(category, searchStr, listText)
  } else {
    await Search(category, searchStr)
  }
  let toggle: Component =
    await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text(searchStr)))
  await driver.delayMs(1500)
  if (await toggle.isChecked() !== clickBool) {
    await toggle.click();
  }
}

export async function searchToggle(toggleName: string, currentText: string, listText?: string, titles?: string) {
  let selection: string | undefined = AppStorage.get('selection')
  let textSearch: Component = await driver.findComponent(ON.text(titles ? '参数列表' : '基础属性'))
  await textSearch.click()
  if (selection != listText) {
    let scrolls: Component = await driver.findComponent(ON.id('scroll'));
    let title: Component = await scrolls.scrollSearch(ON.text(listText)
      .isBefore(ON.type('Image'))
      .within(ON.type('Row'))
      .within(ON.type('ListItemGroup'))
      .within(ON.type('List')))
    await title.click()
  }
  let scrolls: Component = await driver.findComponent(ON.id('scroll'));
  let title: Component = await scrolls.scrollSearch(ON.text(currentText))
  if (!title) {

    let titles: Component = await scrolls.scrollSearch(ON.text(toggleName))
    if (titles) {
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text(toggleName)))
      await toggle.click();
    }
  }
}
import { describe, beforeAll, it} from '@ohos/hypium'
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  titleSearch,
} from '../../../utils';
import { ScrollBarStart } from './ScrollBar';

export default function ScrollBar4() {
  describe('ScrollBar4', () => {
    beforeAll(async (done: Function) => {
      await ScrollBarStart(done)
    })
    it('ArkUI_ScrollBar_Comp_0340', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0341', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0342', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number1
    it('ArkUI_ScrollBar_Comp_0343', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.number1', '通用属性3')

      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.color2
    it('ArkUI_ScrollBar_Comp_0344', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0345', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0346', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0347', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0348', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0349', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number2
    it('ArkUI_ScrollBar_Comp_0350', 0, async (done: Function) => {
      await titleSearch('基础属性', 'linearGradient.number2', '通用属性3')
      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.repeating
    it('ArkUI_ScrollBar_Comp_0351', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_ScrollBar_Comp_0352', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })
  })
}
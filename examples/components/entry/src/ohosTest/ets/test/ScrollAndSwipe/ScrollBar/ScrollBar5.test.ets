import { describe, beforeAll, it} from '@ohos/hypium'
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  Slide,
  sliderDrag,
  ToggleClick,
  titleSearch,
} from '../../../utils';
import { ScrollBarStart } from './ScrollBar';
import { Driver, ON } from '@kit.TestKit';

const driver = Driver.create();

export default function ScrollBar5() {
  describe('ScrollBar5', () => {
    beforeAll(async (done: Function) => {
      await ScrollBarStart(done)
    })
    it('ArkUI_ScrollBar_Comp_0438', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0439', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0440', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0441', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0442', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.opacity
    it('ArkUI_ScrollBar_Comp_0443', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.opacity', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.translateX
    it('ArkUI_ScrollBar_Comp_0444', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateX', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.translateY
    it('ArkUI_ScrollBar_Comp_0445', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateY', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.translateZ
    it('ArkUI_ScrollBar_Comp_0446', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateZ', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.scaleX
    it('ArkUI_ScrollBar_Comp_0447', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleX', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.scaleY
    it('ArkUI_ScrollBar_Comp_0448', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleY', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.scaleZ
    it('ArkUI_ScrollBar_Comp_0449', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleZ', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.scale.centerX
    it('ArkUI_ScrollBar_Comp_0450', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerX', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.scale.centerY
    it('ArkUI_ScrollBar_Comp_0451', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.RotateX
    it('ArkUI_ScrollBar_Comp_0452', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateX', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.RotateY
    it('ArkUI_ScrollBar_Comp_0453', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateY', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.RotateZ
    it('ArkUI_ScrollBar_Comp_0454', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateZ', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.Rotate.CenterX
    it('ArkUI_ScrollBar_Comp_0455', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.Rotate.CenterX', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.Rotate.CenterY
    it('ArkUI_ScrollBar_Comp_0456', 0, async (done: Function) => {

      await titleSearch('基础属性', ' bindPopup.transition.Rotate.CenterY', '通用属性3')

      //取不到bindPopup属性值
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

      done()
    })

    // bindPopup.transition.move
    it('ArkUI_ScrollBar_Comp_0457', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0458', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0459', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0460', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //focusable
    it('ArkUI_ScrollBar_Comp_0461', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0462', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_ScrollBar_Comp_0463', 0, async (done: Function) => {
      //设置当前组件是否为当前页面上的默认焦点，仅在初次创建的页面第一次进入时生效。
      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0464', 0, async (done: Function) => {

      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // groupDefaultFocus
    it('ArkUI_ScrollBar_Comp_0465', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0466', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusOnTouch
    it('ArkUI_ScrollBar_Comp_0467', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0468', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_ScrollBar_Comp_0469', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.margin', '通用属性3')

      //取不到focusBox值
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

      done()
    })

    // focusBox.strokeColor
    it('ArkUI_ScrollBar_Comp_0470', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0471', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0472', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0473', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0474', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_ScrollBar_Comp_0475', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // focusBox.strokeWidth
    it('ArkUI_ScrollBar_Comp_0476', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeWidth', '通用属性3')

      //取不到focusBox值
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

      done()
    })
  })
}
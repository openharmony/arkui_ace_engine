import { ColorBlock, RadioBlock, SliderBlock } from 'common';


@Component
export struct CompSheetTransitionBlocks {
  @Link enableCompBindSheetIsShow: boolean;
  @Link compBindSheetIsShow: boolean;
  @Link enableCompBindSheetOptionsHeight: boolean;
  @Link compBindSheetOptionsHeight: SheetSize;
  @Link enableCompBindSheetOptionsDetents: boolean;
  @Link compBindSheetOptionsDetents: [(SheetSize | Length), (SheetSize | Length)?, (SheetSize | Length)?];
  @Link enableCompBindSheetOptionsPreferType: boolean;
  @Link compBindSheetOptionsPreferType: SheetType;
  @Link enableCompBindSheetOptionsShowClose: boolean;
  @Link compBindSheetOptionsShowClose: boolean;
  @Link enableCompBindSheetOptionsDragBar: boolean;
  @Link compBindSheetOptionsDragBar: boolean;
  @Link enableCompBindSheetOptionsBlurStyle: boolean;
  @Link compBindSheetOptionsBlurStyle: BlurStyle;
  @Link enableCompBindSheetOptionsMaskColor: boolean;
  @Link compBindSheetOptionsMaskColor: ResourceColor | undefined;
  @Link enableCompBindSheetOptionsTitleTitle: boolean;
  @Link compBindSheetOptionsTitleTitle: boolean;
  @Link enableCompBindSheetOptionsTitleSubtitle: boolean;
  @Link compBindSheetOptionsTitleSubtitle: boolean;
  @Link enableCompBindSheetOptionsEnableOutsideInteractive: boolean;
  @Link compBindSheetOptionsEnableOutsideInteractive: boolean;
  @Link enableCompBindSheetOptionsBorderWidth: boolean;
  @Link compBindSheetOptionsBorderWidth: number;
  @Link enableCompBindSheetOptionsBorderColor: boolean;
  @Link compBindSheetOptionsBorderColor: ResourceColor;
  @Link enableCompBindSheetOptionsBorderStyle: boolean;
  @Link compBindSheetOptionsBorderStyle: BorderStyle;
  @Link enableCompBindSheetOptionWidth: boolean;
  @Link compBindSheetOptionsWidth: number;
  @Link enableCompBindSheetOptionShadow: boolean;
  @Link compBindSheetOptionShadow: ShadowStyle;
  @Link enableCompBindSheetOptionMode: boolean;
  @Link compBindSheetOptionMode: SheetMode;
  @Link enableCompBindSheetOptionScrollSizeMode: boolean;
  @Link compBindSheetOptionScrollSizeMode: ScrollSizeMode;

  build() {
    Column() {
      RadioBlock({
        title: 'bindSheet.isShow',
        isEnabled: $enableCompBindSheetIsShow,
        value: $compBindSheetIsShow,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
      if (this.enableCompBindSheetIsShow) {
        RadioBlock({
          title: 'bindSheet.options.height',
          isEnabled: $enableCompBindSheetOptionsHeight,
          value: $compBindSheetOptionsHeight,
          dataSource: [
            { label: 'MEDIUM', value: SheetSize.MEDIUM },
            { label: 'LARGE', value: SheetSize.LARGE },
            { label: 'FIT_CONTENT', value: SheetSize.FIT_CONTENT },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.detents',
          isEnabled: $enableCompBindSheetOptionsDetents,
          value: $compBindSheetOptionsDetents,
          dataSource: [
            { label: 'MEDIUM,LARGE,FIT_CONTENT', value: [SheetSize.MEDIUM, SheetSize.LARGE, SheetSize.FIT_CONTENT] },
            { label: 'LARGE,FIT_CONTENT', value: [SheetSize.LARGE, SheetSize.FIT_CONTENT] },
            { label: 'FIT_CONTENT', value: SheetSize.FIT_CONTENT },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.preferType',
          isEnabled: $enableCompBindSheetOptionsPreferType,
          value: $compBindSheetOptionsPreferType,
          dataSource: [
            { label: 'BOTTOM', value: SheetType.BOTTOM },
            { label: 'CENTER', value: SheetType.CENTER },
            { label: 'POPUP', value: SheetType.POPUP },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.showClose',
          isEnabled: $enableCompBindSheetOptionsShowClose,
          value: $compBindSheetOptionsShowClose,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.dragBar',
          isEnabled: $enableCompBindSheetOptionsDragBar,
          value: $compBindSheetOptionsDragBar,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.blurStyle',
          isEnabled: $enableCompBindSheetOptionsBlurStyle,
          value: $compBindSheetOptionsBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_THIN', value: BlurStyle.COMPONENT_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })
        ColorBlock({
          title: 'bindSheet.options.maskColor',
          isEnabled: $enableCompBindSheetOptionsMaskColor,
          color: $compBindSheetOptionsMaskColor
        })
        RadioBlock({
          title: 'bindSheet.options.title.title',
          isEnabled: $enableCompBindSheetOptionsTitleTitle,
          value: $compBindSheetOptionsTitleTitle,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.title.subtitle',
          isEnabled: $enableCompBindSheetOptionsTitleSubtitle,
          value: $compBindSheetOptionsTitleSubtitle,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.enableOutsideInteractive',
          isEnabled: $enableCompBindSheetOptionsEnableOutsideInteractive,
          value: $compBindSheetOptionsEnableOutsideInteractive,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        SliderBlock({
          title: 'bindSheet.options.borderWidth',
          isEnabled: $enableCompBindSheetOptionsBorderWidth,
          value: $compBindSheetOptionsBorderWidth,
          min: 0,
          max: 32
        })
        ColorBlock({
          title: 'bindSheet.options.borderColor',
          isEnabled: $enableCompBindSheetOptionsBorderColor,
          color: $compBindSheetOptionsBorderColor
        })
        RadioBlock({
          title: 'bindSheet.options.borderStyle',
          isEnabled: $enableCompBindSheetOptionsBorderStyle,
          value: $compBindSheetOptionsBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid }
          ]
        })
        SliderBlock({
          title: 'bindSheet.options.width',
          isEnabled: $enableCompBindSheetOptionWidth,
          value: $compBindSheetOptionsBorderWidth,
          min: 0,
          max: 32
        })
        RadioBlock({
          title: 'bindSheet.options.shadow',
          isEnabled: $enableCompBindSheetOptionShadow,
          value: $compBindSheetOptionShadow,
          dataSource: [
            { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
            { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
            { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
            { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
            { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
            { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.mode',
          isEnabled: $enableCompBindSheetOptionMode,
          value: $compBindSheetOptionMode,
          dataSource: [
            { label: 'OVERLAY', value: SheetMode.OVERLAY },
            { label: 'EMBEDDED', value: SheetMode.EMBEDDED },
          ]
        })
        RadioBlock({
          title: 'bindSheet.options.scrollSizeMode',
          isEnabled: $enableCompBindSheetOptionScrollSizeMode,
          value: $compBindSheetOptionScrollSizeMode,
          dataSource: [
            { label: 'FOLLOW_DETENT', value: ScrollSizeMode.FOLLOW_DETENT },
            { label: 'CONTINUOUS', value: ScrollSizeMode.CONTINUOUS },
          ]
        })
      }
    }
  }
}
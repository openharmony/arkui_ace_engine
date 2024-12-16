import { ColorBlock, IconBlock, RadioBlock, SliderBlock } from 'common';

@Component
export struct CompMenuControlBlocks {
  @Link enableCompBindMenuStartIcon: boolean;
  @Link compBindMenuStartIcon: boolean;
  @Link compBindMenuStartIconStr: ResourceStr;
  @Link enableCompBindMenuEndIcon: boolean;
  @Link compBindMenuEndIcon: boolean;
  @Link compBindMenuEndIconStr: ResourceStr;
  @Link enableCompBindMenuSelect: boolean;
  @Link compBindMenuSelect: boolean;
  @Link enableCompBindMenuSelect2: boolean;
  @Link compBindMenuSelect2: boolean;
  @Link enableCompBindMenuSelect3: boolean;
  @Link compBindMenuSelect3: boolean;
  @Link enableCompBindMenuSelect4: boolean;
  @Link compBindMenuSelect4: boolean;
  @Link enableCompBindMenuDirection: boolean;
  @Link compBindMenuComDirection: Direction;
  @Link enableCompBindMenuSelectIcon: boolean;
  @Link compBindMenuSelectIcon: ResourceStr;
  @Link enableCompBindMenuSelectIcon2: boolean;
  @Link compBindMenuSelectIcon2: ResourceStr;
  @Link enableCompBindMenuSelectIcon3: boolean;
  @Link compBindMenuSelectIcon3: ResourceStr;
  @Link enableCompBindMenuSelectIcon4: boolean;
  @Link compBindMenuSelectIcon4: ResourceStr;
  @Link enableCompBindMenuMenuFontSize: boolean;
  @Link compBindMenuMenuFontSize: number;
  @Link enableCompBindMenuMenuFontWeight: boolean;
  @Link compBindMenuMenuFontWeight: FontWeight;
  @Link enableCompBindMenuMenuFontStyle: boolean;
  @Link compBindMenuMenuFontStyle: FontStyle;
  @Link enableCompBindMenuMenuFontColor: boolean;
  @Link compBindMenuMenuFontColor: ResourceStr;
  @Link enableCompBindMenuMenuRadius: boolean;
  @Link compBindMenuMenuRadius: number;
  @Link enableCompBindMenuMenuWidth: boolean;
  @Link compBindMenuMenuWidth: number;
  @Link enableCompBindMenuMenuHeight: boolean;
  @Link compBindMenuMenuHeight: number;
  @Link enableCompBindMenuMenuItemDividerStrokeWidth: boolean;
  @Link compBindMenuMenuItemDividerStrokeWidth: number;
  @Link enableCompBindMenuMenuItemDividerColor: boolean;
  @Link compBindMenuMenuItemDividerColor: ResourceStr;
  @Link enableCompBindMenuMenuItemDividerStartMargin: boolean;
  @Link compBindMenuMenuItemDividerStartMargin: number;
  @Link enableCompBindMenuMenuItemDividerEndMargin: boolean;
  @Link compBindMenuMenuItemDividerEndMargin: number;
  @Link enableCompBindMenuMenuItemGroupDividerStrokeWidth: boolean;
  @Link compBindMenuMenuItemGroupDividerStrokeWidth: number;
  @Link enableCompBindMenuMenuItemGroupDividerColor: boolean;
  @Link compBindMenuMenuItemGroupDividerColor: ResourceStr;
  @Link enableCompBindMenuMenuItemGroupDividerStartMargin: boolean;
  @Link compBindMenuMenuItemGroupDividerStartMargin: number;
  @Link enableCompBindMenuMenuItemGroupDividerEndMargin: boolean;
  @Link compBindMenuMenuItemGroupDividerEndMargin: number;
  @Link enableCompBindMenuSubMenuExpandingMode: boolean;
  @Link compBindMenuSubMenuExpandingMode: SubMenuExpandingMode;
  @Link enableCompBindMenuMenuBackgroundColor: boolean;
  @Link compBindMenuMenuBackgroundColor: ResourceStr;
  @Link enableCompBindMenuMenuOpacity: boolean;
  @Link compBindMenuMenuOpacity: number;
  @Link enableCompBindMenuMenuVisibility: boolean;
  @Link compBindMenuMenuVisibility: Visibility;
  @Link enableCompBindMenuMenuPadding: boolean;
  @Link compBindMenuMenuPadding: number;
  @Link enableCompBindMenuMenuMargin: boolean;
  @Link compBindMenuMenuMargin: number;

  build() {
    Column() {
      SliderBlock({
        title: 'bindMenu.font.size',
        isEnabled: $enableCompBindMenuMenuFontSize,
        value: $compBindMenuMenuFontSize,
        min: 16,
        max: 24
      })

      RadioBlock({
        title: 'bindMenu.font.weight',
        isEnabled: $enableCompBindMenuMenuFontWeight,
        value: $compBindMenuMenuFontWeight,
        dataSource: [
          { label: 'Lighter', value: FontWeight.Lighter },
          { label: 'Normal', value: FontWeight.Normal },
          { label: 'Regular', value: FontWeight.Regular },
          { label: 'Medium', value: FontWeight.Medium },
          { label: 'Bold', value: FontWeight.Bold },
          { label: 'Bolder', value: FontWeight.Bolder }
        ]
      })

      RadioBlock({
        title: 'bindMenu.font.style',
        isEnabled: $enableCompBindMenuMenuFontStyle,
        value: $compBindMenuMenuFontStyle,
        dataSource: [
          { label: 'Normal', value: FontWeight.Lighter },
          { label: 'Italic', value: FontWeight.Normal }
        ]
      })

      ColorBlock({
        title: 'bindMenu.fontColor',
        isEnabled: $enableCompBindMenuMenuFontColor,
        color: $compBindMenuMenuFontColor,
      })

      SliderBlock({
        title: 'bindMenu.radius',
        isEnabled: $enableCompBindMenuMenuRadius,
        value: $compBindMenuMenuRadius,
        min: 0,
        max: 16
      })

      SliderBlock({
        title: 'bindMenu.width',
        isEnabled: $enableCompBindMenuMenuWidth,
        value: $compBindMenuMenuWidth,
        min: 100,
        max: 150
      })

      SliderBlock({
        title: 'bindMenu.height',
        isEnabled: $enableCompBindMenuMenuHeight,
        value: $compBindMenuMenuHeight,
        min: 250,
        max: 450
      })

      ColorBlock({
        title: 'bindMenu.menuItemDivider.color',
        isEnabled: $enableCompBindMenuMenuItemDividerColor,
        color: $compBindMenuMenuItemDividerColor,
      })

      SliderBlock({
        title: 'bindMenu.menuItemDivider.strokeWidth',
        isEnabled: $enableCompBindMenuMenuItemDividerStrokeWidth,
        value: $compBindMenuMenuItemDividerStrokeWidth,
        min: 1,
        max: 5
      })

      SliderBlock({
        title: 'bindMenu.menuItemDivider.startMargin',
        isEnabled: $enableCompBindMenuMenuItemDividerStartMargin,
        value: $compBindMenuMenuItemDividerStartMargin,
        min: 16,
        max: 32
      })

      SliderBlock({
        title: 'bindMenu.menuItemDivider.endMargin',
        isEnabled: $enableCompBindMenuMenuItemDividerEndMargin,
        value: $compBindMenuMenuItemDividerEndMargin,
        min: 16,
        max: 32
      })

      SliderBlock({
        title: 'bindMenu.menuItemGroupDivider.strokeWidth',
        isEnabled: $enableCompBindMenuMenuItemGroupDividerStrokeWidth,
        value: $compBindMenuMenuItemGroupDividerStrokeWidth,
        min: 1,
        max: 5
      })

      ColorBlock({
        title: 'bindMenu.menuItemGroupDivider.color',
        isEnabled: $enableCompBindMenuMenuItemGroupDividerColor,
        color: $compBindMenuMenuItemGroupDividerColor,
      })

      SliderBlock({
        title: 'bindMenu.menuItemGroupDivider.startMargin',
        isEnabled: $enableCompBindMenuMenuItemGroupDividerStartMargin,
        value: $compBindMenuMenuItemGroupDividerStartMargin,
        min: 16,
        max: 32
      })

      SliderBlock({
        title: 'bindMenu.menuItemGroupDivider.endMargin',
        isEnabled: $enableCompBindMenuMenuItemGroupDividerEndMargin,
        value: $compBindMenuMenuItemGroupDividerEndMargin,
        min: 16,
        max: 32
      })

      RadioBlock({
        title: 'bindMenu.SubMenuExpandingMode',
        isEnabled: $enableCompBindMenuSubMenuExpandingMode,
        value: $compBindMenuSubMenuExpandingMode,
        dataSource: [
          { label: 'SIDE_EXPAND', value: SubMenuExpandingMode.SIDE_EXPAND },
          { label: 'EMBEDDED_EXPAND', value: SubMenuExpandingMode.EMBEDDED_EXPAND },
          { label: 'STACK_EXPAND', value: SubMenuExpandingMode.STACK_EXPAND }
        ]
      })

      RadioBlock({
        title: 'bindMenu.direction',
        isEnabled: $enableCompBindMenuDirection,
        value: $compBindMenuComDirection,
        dataSource: [
          { label: 'Auto', value: Direction.Auto },
          { label: 'Rtl', value: Direction.Rtl },
          { label: 'Ltr', value: Direction.Ltr }
        ]
      })

      RadioBlock({
        title: 'bindMenu.菜单项1是否选中',
        isEnabled: $enableCompBindMenuSelect,
        value: $compBindMenuSelect,
        dataSource: [
          { label: '选中', value: true },
          { label: '取消', value: false }
        ]
      })

      if (this.compBindMenuSelect) {
        IconBlock({
          title: 'bindMenu.是否显示选中图标',
          isEnabled: $enableCompBindMenuSelectIcon,
          icon: $compBindMenuSelectIcon,
        })
      }

      RadioBlock({
        title: 'bindMenu.菜单项2是否选中',
        isEnabled: $enableCompBindMenuSelect2,
        value: $compBindMenuSelect2,
        dataSource: [
          { label: '选中', value: true },
          { label: '取消', value: false }
        ]
      })

      if (this.compBindMenuSelect2) {
        IconBlock({
          title: 'bindMenu.是否显示选中图标',
          isEnabled: $enableCompBindMenuSelectIcon2,
          icon: $compBindMenuSelectIcon2,
        })
      }

      RadioBlock({
        title: 'bindMenu.菜单项3是否选中',
        isEnabled: $enableCompBindMenuSelect3,
        value: $compBindMenuSelect3,
        dataSource: [
          { label: '选中', value: true },
          { label: '取消', value: false }
        ]
      })

      if (this.compBindMenuSelect3) {
        IconBlock({
          title: 'bindMenu.是否显示选中图标',
          isEnabled: $enableCompBindMenuSelectIcon3,
          icon: $compBindMenuSelectIcon3,
        })
      }

      RadioBlock({
        title: 'bindMenu.菜单项4是否选中',
        isEnabled: $enableCompBindMenuSelect4,
        value: $compBindMenuSelect4,
        dataSource: [
          { label: '选中', value: true },
          { label: '取消', value: false }
        ]
      })

      if (this.compBindMenuSelect4) {
        IconBlock({
          title: 'bindMenu.是否显示选中图标',
          isEnabled: $enableCompBindMenuSelectIcon4,
          icon: $compBindMenuSelectIcon4,
        })
      }

      RadioBlock({
        title: 'bindMenu.是否显示前缀图标',
        isEnabled: $enableCompBindMenuStartIcon,
        value: $compBindMenuStartIcon,
        dataSource: [
          { label: '显示', value: true },
          { label: '隐藏', value: false }
        ]
      })

      RadioBlock({
        title: 'bindMenu.item中是否显示右侧图标',
        isEnabled: $enableCompBindMenuEndIcon,
        value: $compBindMenuEndIcon,
        dataSource: [
          { label: '显示', value: true },
          { label: '隐藏', value: false }
        ]
      })

      ColorBlock({
        title: 'bindMenu.BackgroundColor',
        isEnabled: $enableCompBindMenuMenuBackgroundColor,
        color: $compBindMenuMenuBackgroundColor,
      })

      SliderBlock({
        title: 'bindMenu.Opacity',
        isEnabled: $enableCompBindMenuMenuOpacity,
        value: $compBindMenuMenuOpacity,
        step: 0.1,
        min: 0,
        max: 1
      })

      RadioBlock({
        title: 'bindMenu.Visibility',
        isEnabled: $enableCompBindMenuMenuVisibility,
        value: $compBindMenuMenuVisibility,
        dataSource: [
          { label: 'Visible', value: Visibility.Visible },
          { label: 'Hidden', value: Visibility.Hidden }
        ]
      })

      SliderBlock({
        title: 'bindMenu.Padding',
        isEnabled: $enableCompBindMenuMenuPadding,
        value: $compBindMenuMenuPadding,
        min: 0,
        max: 16
      })

      SliderBlock({
        title: 'bindMenu.Margin',
        isEnabled: $enableCompBindMenuMenuMargin,
        value: $compBindMenuMenuMargin,
        min: 0,
        max: 16
      })
    }
    .width('100%')
  }
}
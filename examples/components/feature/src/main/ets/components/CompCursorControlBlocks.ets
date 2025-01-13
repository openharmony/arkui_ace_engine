import { RadioBlock } from 'common';
import { pointer } from '@kit.InputKit';

@Component
export struct CompCursorControlBlocks {
  @Link enableCompCursorControl: boolean;
  @Link compCursorControl: PointerStyle;

  build() {
    Column() {
      RadioBlock({
        title: 'cursorControl',
        isEnabled: $enableCompCursorControl,
        value: $compCursorControl,
        dataSource: [
          { label: 'DEFAULT', value: pointer.PointerStyle.DEFAULT },
          { label: 'EAST', value: pointer.PointerStyle.EAST },
          { label: 'WEST', value: pointer.PointerStyle.WEST },
          { label: 'SOUTH', value: pointer.PointerStyle.SOUTH },
          { label: 'NORTH', value: pointer.PointerStyle.NORTH },
          { label: 'WEST_EAST', value: pointer.PointerStyle.WEST_EAST },
          { label: 'NORTH_SOUTH', value: pointer.PointerStyle.NORTH_SOUTH },
          { label: 'NORTH_EAST', value: pointer.PointerStyle.NORTH_EAST },
          { label: 'NORTH_WEST', value: pointer.PointerStyle.NORTH_WEST },
          { label: 'SOUTH_EAST', value: pointer.PointerStyle.SOUTH_EAST },
          { label: 'SOUTH_WEST', value: pointer.PointerStyle.SOUTH_WEST },
          { label: 'NORTH_EAST_SOUTH_WEST', value: pointer.PointerStyle.NORTH_EAST_SOUTH_WEST },
          { label: 'NORTH_WEST_SOUTH_EAST', value: pointer.PointerStyle.NORTH_WEST_SOUTH_EAST },
          { label: 'CROSS', value: pointer.PointerStyle.CROSS },
          { label: 'CURSOR_COPY', value: pointer.PointerStyle.CURSOR_COPY },
          { label: 'CURSOR_FORBID', value: pointer.PointerStyle.CURSOR_FORBID },
          { label: 'COLOR_SUCKER', value: pointer.PointerStyle.COLOR_SUCKER },
          { label: 'HAND_GRABBING', value: pointer.PointerStyle.HAND_GRABBING },
          { label: 'HAND_OPEN', value: pointer.PointerStyle.HAND_OPEN },
          { label: 'HAND_POINTING', value: pointer.PointerStyle.HAND_POINTING },
          { label: 'HELP', value: pointer.PointerStyle.HELP },
          { label: 'MOVE', value: pointer.PointerStyle.MOVE },
          { label: 'RESIZE_LEFT_RIGHT', value: pointer.PointerStyle.RESIZE_LEFT_RIGHT },
          { label: 'RESIZE_UP_DOWN', value: pointer.PointerStyle.RESIZE_UP_DOWN },
          { label: 'SCREENSHOT_CHOOSE', value: pointer.PointerStyle.SCREENSHOT_CHOOSE },
          { label: 'SCREENSHOT_CURSOR', value: pointer.PointerStyle.SCREENSHOT_CURSOR },
          { label: 'TEXT_CURSOR', value: pointer.PointerStyle.TEXT_CURSOR },
          { label: 'ZOOM_IN', value: pointer.PointerStyle.ZOOM_IN },
          { label: 'ZOOM_OUT', value: pointer.PointerStyle.ZOOM_OUT },
          { label: 'MIDDLE_BTN_EAST', value: pointer.PointerStyle.MIDDLE_BTN_EAST },
          { label: 'MIDDLE_BTN_WEST', value: pointer.PointerStyle.MIDDLE_BTN_WEST },
          { label: 'MIDDLE_BTN_SOUTH', value: pointer.PointerStyle.MIDDLE_BTN_SOUTH },
          { label: 'MIDDLE_BTN_NORTH', value: pointer.PointerStyle.MIDDLE_BTN_NORTH },
          { label: 'MIDDLE_BTN_NORTH_SOUTH', value: pointer.PointerStyle.MIDDLE_BTN_NORTH_SOUTH },
          { label: 'MIDDLE_BTN_NORTH_EAST', value: pointer.PointerStyle.MIDDLE_BTN_NORTH_EAST },
          { label: 'MIDDLE_BTN_NORTH_WEST', value: pointer.PointerStyle.MIDDLE_BTN_NORTH_WEST },
          { label: 'MIDDLE_BTN_SOUTH_EAST', value: pointer.PointerStyle.MIDDLE_BTN_SOUTH_EAST },
          { label: 'MIDDLE_BTN_SOUTH_WEST', value: pointer.PointerStyle.MIDDLE_BTN_SOUTH_WEST },
          { label: 'MIDDLE_BTN_NORTH_SOUTH_WEST_EAST', value: pointer.PointerStyle.MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
          { label: 'HORIZONTAL_TEXT_CURSOR', value: pointer.PointerStyle.HORIZONTAL_TEXT_CURSOR },
          { label: 'CURSOR_CROSS', value: pointer.PointerStyle.CURSOR_CROSS },
          { label: 'CURSOR_CIRCLE', value: pointer.PointerStyle.CURSOR_CIRCLE },
          { label: 'LOADING', value: pointer.PointerStyle.LOADING },
          { label: 'RUNNING', value: pointer.PointerStyle.RUNNING }
        ]
      })
    }
  }
}
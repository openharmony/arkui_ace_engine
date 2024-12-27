import { RadioBlock, SliderBlock } from 'common';


@Component
export struct CompDragAndDropControlBlocks {
  @Link enableCompDraggable: boolean;
  @Link compDraggable: boolean;
  @Link enableCompDragPreview: boolean;
  @Link compDragPreview: string;
  @Link enableCompDragPreviewOptionsValueMode: boolean;
  @Link compDragPreviewOptionsValueMode: DragPreviewMode;
  @Link enableCompDragPreviewOptionsValueNumberBadge: boolean;
  @Link compDragPreviewOptionsValueNumberBadge: number;
  @Link enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled: boolean;
  @Link compDragPreviewOptionsOptionsIsMultiSelectionEnabled: boolean;
  @Link enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting: boolean;
  @Link compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'draggable',
        isEnabled: $enableCompDraggable,
        value: $compDraggable,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
      if (this.enableCompDraggable) {
        RadioBlock({
          title: 'dragPreview',
          isEnabled: $enableCompDragPreview,
          value: $compDragPreview,
          dataSource: [
            { label: '默认', value: '默认' },
            { label: '文本', value: '文本' },
            { label: '字符串', value: '字符串' },
          ]
        })
        RadioBlock({
          title: 'dragPreviewOptions.value.mode',
          isEnabled: $enableCompDragPreviewOptionsValueMode,
          value: $compDragPreviewOptionsValueMode,
          dataSource: [
            { label: 'AUTO', value: DragPreviewMode.AUTO },
            { label: 'DISABLE_SCALE', value: DragPreviewMode.DISABLE_SCALE },
            { label: 'ENABLE_DEFAULT_SHADOW', value: DragPreviewMode.ENABLE_DEFAULT_SHADOW },
            { label: 'ENABLE_DEFAULT_RADIUS', value: DragPreviewMode.ENABLE_DEFAULT_RADIUS },
          ]
        })
        SliderBlock({
          title: 'dragPreviewOptions.value.numberBadge',
          isEnabled: $enableCompDragPreviewOptionsValueNumberBadge,
          value: $compDragPreviewOptionsValueNumberBadge,
          min: 0,
          max: 48
        })
        RadioBlock({
          title: 'dragPreviewOptions.options.isMultiSelectionEnabled',
          isEnabled: $enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled,
          value: $compDragPreviewOptionsOptionsIsMultiSelectionEnabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
        RadioBlock({
          title: 'dragPreviewOptions.options.defaultAnimationBeforeLifting',
          isEnabled: $enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting,
          value: $compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
      }
    }
  }
}
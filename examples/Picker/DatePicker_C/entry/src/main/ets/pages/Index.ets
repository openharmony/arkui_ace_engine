import render from 'libentry.so';

@Entry
@Component
struct Index {
  build() {
    Column() {
      Row() {
        XComponent({
          id: 'xComponentId',
          type: XComponentType.NODE,
          libraryname: 'entry'
        }).onDestroy(() => {
          console.log('onDestroy');
        }).onAppear(() => {
          console.log('[date_picker C] index.ets');
          render.datePickerTest('xComponentId')
        }).width('100%')
          .height('100%')
      }
    }
    .height('100%')
  }
}

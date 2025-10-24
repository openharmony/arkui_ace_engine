import entry from 'libentry.so';

@Entry
@Component
struct NativePage {
  @State text: string = "Hello, Native";
  @State tag: string = 'NativePage';

  build() {
    Column({ space: 10 }) {
      XComponent({
        id: this.tag,
        type: 'node',
        libraryname: 'entry'
      }).onDestroy(() => {
        console.log('onDestroy');
      }).backgroundColor('#FFEEEEEE')
        .width('100%')
        .height('100%')
    }
    .height('100%')
    .width('100%')
    .onAppear(() => {
      entry.SwipeActionTest(this.tag);
    })
  }
}
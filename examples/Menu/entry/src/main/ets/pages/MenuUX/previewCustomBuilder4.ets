import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';

@Entry
@Component
struct previewMenuBuilder4 {
  @State imgState: Visibility = Visibility.Visible;
  @State img: Resource = $r('app.media.app_icon')
  @State blockArr: string[] = []
  @State targetImage: string = '';

  @Builder imgBuilder(){
    Image(this.img)
      .width(100)
      .height(100)
      .draggable(true)
      .visibility(this.imgState)
      .onDragStart((event: DragEvent)=>{
        let data: UDC.Image = new UDC.Image();
        data.imageUri = '/resources/base/media/app_icon.png'
        let unifiedData = new UDC.UnifiedData(data);
        event.setData(unifiedData);
      })
  }

  @Builder
  MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: (): void => this.imgBuilder()
      })
    }
  }

  build() {
    Column() {
      Text('LongPress preview: CustomBuilder Image').margin({ top:10,bottom:30 })
      Text('LongPress to show Image').margin(20)
        .fontSize(25)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          preview: this.imgBuilder
        })

      Column(){
        Text('Image图片释放区域')
          .fontSize('15dp')
          .height('30%')
        List(){
          ForEach(this.BblockArr, (item: string) => {
            ListItem() {
              Image(item)
                .width(100)
                .height(100)
                .border({width: 1})
            }
            .margin(20)
          }, (item: string) => item)
        }
        .border({width: 1})
        .height('90%')
        .width('90%')
        .allowDrop([UTD.UniformDataType.IMAGE])
        .onDrop((event: DragEvent)=>{
          let records:Array<UDC.UnifiedRecord> = event.getData().getRecords();
          this.targetImage = (records[0] as UDC.Image).imageUri;
          this.BblockArr.push(this.targetImage)
          console.log('targetImage：' + this.targetImage);
          if(records.length > 0) {
            this.imgState = Visibility.Visible;
            console.info('in drop')
          }
        })
      }
    }
    .width('100%')
    .height('100%')
  }
}
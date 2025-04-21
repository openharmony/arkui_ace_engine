@Entry
@Component
struct ConstraintSize {
  build() {
    Scroll() {
      Flex({ justifyContent: FlexAlign.Center, }) {
        Column({ space: 10 }) {
          Text() {
            Span('TextInput constraintSize布局规格:\n')
            Span('规格1.实际文本内容+padding+孩子大小<= minwidth时，按minwidth作为组件宽 \n')
            Span('规格2.minwidth<实际文本内容+padding+孩子大小 <=maxwidth时，按实际文本内容+padding+孩子大小作为组件宽高 \n')
            Span('规格3.实际文本内容+padding+孩子大小 > maxwidth时,按maxwidth作为组件宽度 \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Column() {
            Text('规格1.实际文本内容+padding+孩子大小<= minwidth时，按minwidth作为组件宽 \n')
            Text('设置constraintSize的文本框宽度大于未设置constraintSize文本框 pass \n').fontColor(Color.Red)
            TextInput({ placeholder: '未设置constraintSize' })
              .width(100)
              .padding(20)
            TextInput({ placeholder: '设置constraintSize' })
              .constraintSize({ minWidth: 200 })
              .width(100)
              .padding(20)

            Column() {
              Text('规格2.minwidth<实际文本内容+padding+孩子大小 <=maxwidth时，按实际文本内容+padding+孩子大小作为组件宽高 \n')
              Text('设置constraintSize的文本框宽度等于未设置constraintSize文本框 pass \n').fontColor(Color.Red)
              TextInput({ placeholder: '未设置constraintSize' })
                .width(250)
                .padding(20)
              TextInput({ placeholder: '设置constraintSize' })
                .constraintSize({ minWidth: 200, maxWidth: 500 })
                .width(250)
                .padding(20)

              Column() {
                Text('规格3.实际文本内容+padding+孩子大小 > maxwidth时,按maxwidth作为组件宽度 \n')
                Text('设置constraintSize的文本框宽度小于未设置constraintSize文本框 pass \n').fontColor(Color.Red)
                TextInput({ placeholder: '未设置constraintSize' })
                  .width(400)
                  .padding(20)
                TextInput({ placeholder: '设置constraintSize' })
                  .constraintSize({ maxWidth: 200 })
                  .width(400)
                  .padding(20)


                Column() {
                  Text('规格4. autoWidth时以实际文本宽度布局撑满可视区域,受minWidth与maxWidth限制； \n')
                  Text('设置constraintSize的文本框宽度小于未设置constraintSize文本框 pass \n').fontColor(Color.Red)
                  TextInput({ placeholder: '未设置constraintSize' })
                    .width('auto')
                    .padding(20)
                  TextInput({ placeholder: '设置maxWidth' })
                    .constraintSize({ maxWidth: 100 })
                    .width('auto')
                    .padding(20)
                  TextInput({ placeholder: '设置minWidth' })
                    .constraintSize({ minWidth: 400 })
                    .width('auto')
                    .padding(20)

                }
              }
            }
          }
        }
      }
    }
  }
}

import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"


@Component
export struct ManyImportComponent168 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)

        }
    }
}


import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent76 } from "./manyImportFile76"
import { ManyImportComponent77 } from "./manyImportFile77"


@Component
export struct ManyImportComponent38 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent76()
            ManyImportComponent77()

        }
    }
}

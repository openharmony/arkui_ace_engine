
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent62 } from "./manyImportFile62"
import { ManyImportComponent63 } from "./manyImportFile63"


@Component
export struct ManyImportComponent31 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent62()
            ManyImportComponent63()

        }
    }
}

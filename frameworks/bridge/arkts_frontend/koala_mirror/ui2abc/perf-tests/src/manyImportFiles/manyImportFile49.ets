
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent98 } from "./manyImportFile98"
import { ManyImportComponent99 } from "./manyImportFile99"


@Component
export struct ManyImportComponent49 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent98()
            ManyImportComponent99()

        }
    }
}
